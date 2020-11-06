/**
 * @file fram.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "fram.hpp"

#define ADDR_LEN_IN_BYTES 3

/***** Private Methods *****/

bool fram::write_byte(uint8_t byte)
{
    return true;
}

uint8_t fram::read_byte()
{
    return 0;
}

/***** Public Methods *****/
fram::fram()
{
}

fram::fram(uint8_t CS)
{
    device = Adafruit_FRAM_SPI(CS);
    next_write_addr = 0;
    next_read_addr = 0; 
    last_packet_len = 0;
}

bool fram::init()
{
    return device.begin(ADDR_LEN_IN_BYTES);
}

DownlinkMessage fram::read()
{
    if (last_packet_len <= 0 || next_read_addr < 0)
    {
        #if DEBUG
            Serial.println("no valid packet in memory");
        #endif
        downlink_proto_SystemMetrics temp;
        DownlinkMessage msg = DownlinkMessage(temp);
        return msg;
    }

    uint8_t rawPacket[last_packet_len];

    for (uint16_t offset = 0; offset < last_packet_len; ++offset)
    {
        rawPacket[offset] = device.read8(uint32_t(next_read_addr) + uint32_t(offset));
    }
    
    next_write_addr = next_read_addr;
    next_read_addr -= last_packet_len;
    
    DownlinkMessage msg(rawPacket);
    return msg;
}

bool fram::write(downlink_proto_SystemMetrics data)
{
    #if DEBUG
        Serial.println("writing in fram class");
    #endif

    DownlinkMessage msg = DownlinkMessage(data);
    uint16_t packet_length = msg.packetLength();
    uint8_t *packet = new uint8_t[packet_length];

    if (msg.packet(packet,packet_length))
    {
        for (uint16_t offset = 0; offset < packet_length; ++offset)
        {
            device.writeEnable(true);
            device.write8(uint32_t(next_write_addr + offset), packet[offset]);
            device.writeEnable(false);
        }
        next_read_addr = next_write_addr;
        next_write_addr += packet_length;
        last_packet_len = packet_length;
        
        delete [] packet;
        return true;
    }
    else
    {
        delete[] packet;
        return false;
    }
}