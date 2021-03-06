// based off of https://beej.us/guide/bgnet/examples/server.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pb_encode.h>
#include <pb_common.h>
#include <iostream>
#include <time.h>

#include "donwlink_message.hpp"
#include "messages.pb.h"

#define PORT "1234"  // the port users will be connecting to

#define BACKLOG 10   // how many pending connections queue will hold

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void generateMetrics(downlink_proto_SystemMetrics* metrics) {
    metrics->has_computer = true;
    metrics->computer.power_current = (rand() % 3000 + 100) / 1000.0f;
    std::cout << "computer.power_current " << metrics->computer.power_current << std::endl;
    metrics->computer.power_voltage = (rand() % 5500 + 4500) / 1000.0f;
    std::cout << "computer.power_voltage " << metrics->computer.power_voltage << std::endl;
    metrics->computer.temperature_die = (rand() % 1000 + 450) / 10.0f;
    std::cout << "computer.temperature_die " << metrics->computer.temperature_die << std::endl;
}

int main(int argc, char** argv) {
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	struct sigaction sa;
	int yes=1;
	char s[INET6_ADDRSTRLEN];
	int rv;

    srand(time(NULL));

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (p == NULL)  {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	printf("server: waiting for connections...\n");

    sin_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
        perror("accept");
        return 1;
    }

    downlink_proto_SystemMetrics metrics = downlink_proto_SystemMetrics_init_zero;
    uint8_t buffer[256];
    while(1) {
        generateMetrics(&metrics);

        DownlinkMessage msg(metrics);

        std::cout << "Checksum " << msg.checksum() << std::endl;
        std::cout << "Data length " << msg.dataLength() << std::endl;

        if(msg.packet(buffer, 256)) {
            std::cout << "Sending" << std::endl;
            send(new_fd, buffer, msg.packetLength(), 0);
        }

        std::cout << std::endl;
        sleep(5);
    }

    close(new_fd);

	return 0;
}
