

#ifndef FRAM_HPP
#define FRAM_HPP

#include "pins.hpp"
#include "messages.pb.h"
#include "Adafruit_FRAM_SPI.h"
#include <inttypes.h>
#include "donwlink_message.hpp"

#define FRAM_BYTE_CAPACITY 2000

class fram
{
private:
    uint8_t cs;
    uint16_t next_write_addr;
    uint16_t next_read_addr;
    uint16_t last_packet_len;
    Adafruit_FRAM_SPI device;

    bool write_byte(uint8_t);

    uint8_t read_byte();

public:
    fram();
    fram(uint8_t CS);

    /**
     * @brief initializes the fram module
     * 
     * @return true 
     * @return false 
     */
    bool init();

    /**
     * @brief reads the data packet from the fram module
     * 
     * @return true 
     * @return false 
     */
    DownlinkMessage read();

    /**
     * @brief writes the packet to the fram module
     * 
     * @return true 
     * @return false 
     */
    bool write(downlink_proto_SystemMetrics data);

};








#endif // FRAM_HPP