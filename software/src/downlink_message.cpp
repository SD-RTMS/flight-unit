#include "donwlink_message.hpp"
#include "messages.pb.h"

DownlinkMessage::DownlinkMessage(uint8_t rawPacket[]) {
    // TODO
}

DownlinkMessage::DownlinkMessage(uint8_t serializedProto[]) {
    // TODO
}

DownlinkMessage::DownlinkMessage(downlink_proto::SystemMetrics& metrics) {
    // TODO
}

bool DownlinkMessage::validateChecksum() {
    return _checksum == _computeChecksum();
}

uint8_t* DownlinkMessage::packet(uint8_t* out, size_t bufferSize) {
    if (packetLength() > bufferSize)
        return false;

    // TODO
    return true;
}

uint16_t DownlinkMessage::dataLength() {
    return _dataLength;
}

uint16_t DownlinkMessage::packetLength() {
    return PACKET_CHECKSUM_LENGTH_BYTES + PACKET_DATALEN_LENGTH_BYTES + _dataLength;
}

uint64_t DownlinkMessage::checksum() {
    return _checksum;
}

bool DownlinkMessage::data(uint8_t* out, size_t bufferSize) {
    if (dataLength() > bufferSize)
        return false;

    // TODO
    return true;
}

uint64_t _computeChecksum() {
    // TODO
    return 0;
}
