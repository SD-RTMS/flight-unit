#pragma once

#include <inttypes.h>
//#include <array>

#include "messages.pb.h"

#define PACKET_CHECKSUM_LENGTH_BYTES    2u
#define PACKET_DATALEN_LENGTH_BYTES     2u
#define PACKET_HEADER_LENGTH_BYTES      (PACKET_CHECKSUM_LENGTH_BYTES + PACKET_DATALEN_LENGTH_BYTES)
#define LOCAL_BUFFER_SIZE               256u

// Convenience class for encapsulation of downlink message data
class DownlinkMessage {
public:
    explicit DownlinkMessage();

    // Construct message from a raw packet of chksum-len-data format, provided from FRAM
    explicit DownlinkMessage(uint8_t rawPacket[]);

    // Construct message from serialized proto
    // Will calculate length and checksum
    explicit DownlinkMessage(uint8_t serializedProto[], size_t length);

    // Construct message from a non-serialized proto
    // Will serialize and calculate message params
    explicit DownlinkMessage(downlink_proto_SystemMetrics& metrics);

    // Copy constructor to allow assignment
    //explicit DownlinkMessage(const DownlinkMessage &msg);

    // Verifies checksum is correct given data
    // Useful if constructed from raw packet
    bool validateChecksum();

    // Writes the encapsulated packet of chksum-len-data format into `out`
    // Returns false if packet cannot fit in the buffer
    bool packet(uint8_t* out, size_t bufferSize);

    // Returns length of the serialized data in bytes
    uint16_t dataLength();

    // Returns length of entire packet in bytes
    uint16_t packetLength();

    // Returns the stored checksum
    uint16_t checksum();

    // Writes the packet data into `out`
    // Returns false if packet cannot fit in the buffer
    bool data(uint8_t* out, size_t bufferSize);

private:
    uint16_t _checksum;
    uint16_t _dataLength;
    uint8_t _serializedProto[LOCAL_BUFFER_SIZE];

    // Computes a checksum from _serializedProto[]
    uint16_t _computeChecksum();
};
