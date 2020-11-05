#ifndef MEMORY_IF_HPP
#define MEMORY_IF_HPP

#include "fram.hpp"
#include "messages.pb.h"

class memory_if
{
private:
    fram device1, device2, device3;
    bool debug;
    
    DownlinkMessage majority_voter(DownlinkMessage d1, DownlinkMessage d2, DownlinkMessage d3);
    bool ecc_check(downlink_proto_SystemMetrics data);

public:
    memory_if();
    ~memory_if();

    bool init();

    DownlinkMessage read();
    
    bool write(downlink_proto_SystemMetrics data);

};


#endif // MEMORY_IF_HPP