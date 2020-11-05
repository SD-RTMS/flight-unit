/**
 * @file digital_io.hpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef DIGITAL_IO_HPP
#define DIGITAL_IO_HPP

#include "messages.pb.h"
#include "pins.hpp"
#include <inttypes.h>

#define NUM_DIGITAL_IO 5
#define NUM_LEDS 3

/**
 * @brief LED signal codes
 * 
 */
typedef enum ledCode
{
    CODE1,
    CODE2,
    CODE3,
    CODE4,
} ledCode;

/**
 * @brief digital i/o bank class
 * 
 */
class digital_io
{
private:
   
public:
    /**
     * @brief initializes the digital i/o bank
     * 
     * @return true - init is successful 
     * @return false - init fails
     */
    bool init();

    /**
     * @brief reads data and updates data struct
     * 
     * @return true - read is successful
     * @return false - read fails
     */
    downlink_proto_SystemMetrics read(downlink_proto_SystemMetrics data);

    /**
     * @brief writes an led pattern code to the digital pin specified
     * 
     * @return true 
     * @return false 
     */
    bool write_led(uint8_t, ledCode);
};

#endif // DIGITAL_IO_HPP