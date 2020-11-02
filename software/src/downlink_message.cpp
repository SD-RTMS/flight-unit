#include <cstring>
#include <pb_encode.h>
#include <pb_common.h>
#include <iostream>

#include "donwlink_message.hpp"
#include "messages.pb.h"

DownlinkMessage::DownlinkMessage(uint8_t rawPacket[]) {
    uint8_t* cur = &rawPacket[0];
    // Parse checksum
    _checksum = *(reinterpret_cast<uint16_t*>(cur));
    cur += PACKET_CHECKSUM_LENGTH_BYTES;
    // Parse data length
    _dataLength = *(reinterpret_cast<uint16_t*>(cur));
    cur += PACKET_DATALEN_LENGTH_BYTES;
    // Copy data to local buffer
    std::memcpy(&_serializedProto[0], cur, _dataLength);
}

DownlinkMessage::DownlinkMessage(uint8_t serializedProto[], size_t length): _dataLength(length) {
    std::memcpy(&_serializedProto[0], &serializedProto[0], _dataLength);
    _checksum = _computeChecksum();
}

DownlinkMessage::DownlinkMessage(downlink_proto_SystemMetrics& metrics) {
    // Serialize the proto into the local buffer and store its size
    pb_ostream_t stream = pb_ostream_from_buffer(&_serializedProto[0], LOCAL_BUFFER_SIZE);
    bool status = pb_encode(&stream, downlink_proto_SystemMetrics_fields, &metrics);
    if(!status)
        std::cout << "serialization error\n";
    _dataLength = stream.bytes_written;
    _checksum = _computeChecksum();
}

bool DownlinkMessage::validateChecksum() {
    return _checksum == _computeChecksum();
}

bool DownlinkMessage::packet(uint8_t* out, size_t bufferSize) {
    if (packetLength() > bufferSize)
        return false;

    // Write headers
    uint16_t* chkptr = reinterpret_cast<uint16_t*>(out);
    uint16_t* lenptr = reinterpret_cast<uint16_t*>(out + PACKET_CHECKSUM_LENGTH_BYTES);
    *chkptr = _checksum;
    *lenptr = _dataLength;

    // Call `data` to copy the buffer into the packet and use its return value
    return data(out+PACKET_HEADER_LENGTH_BYTES, bufferSize-PACKET_HEADER_LENGTH_BYTES);
}

uint16_t DownlinkMessage::dataLength() {
    return _dataLength;
}

uint16_t DownlinkMessage::packetLength() {
    return PACKET_CHECKSUM_LENGTH_BYTES + PACKET_DATALEN_LENGTH_BYTES + _dataLength;
}

uint16_t DownlinkMessage::checksum() {
    return _checksum;
}

bool DownlinkMessage::data(uint8_t* out, size_t bufferSize) {
    if (_dataLength > bufferSize)
        return false;

    // Copy localbuffer into `out`
    std::memcpy(out, &_serializedProto[0], _dataLength);

    return true;
}

uint16_t DownlinkMessage::_computeChecksum() {
    // BSD 16-bit checksum
    uint16_t checksum = 0;

    for (size_t i = 0; i < _dataLength; i++){
        checksum = (checksum >> 1) + ((checksum & 1) << 15);
        checksum += _serializedProto[i];
    }

    return checksum;
}
