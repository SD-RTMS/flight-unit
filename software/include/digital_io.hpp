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

#include "data.hpp"
#include "pins.hpp"
#include <inttypes.h>

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
    const uint8_t bank[5] = {SC_D0, SC_D1, SC_D2, SC_D3, SC_D4};
    const uint8_t leds[3] = {LED_0, LED_1, LED_2}; 
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
    bool read(Data *);

    /**
     * @brief writes an led pattern code to the digital pin specified
     * 
     * @return true 
     * @return false 
     */
    bool write_led(uint8_t, ledCode);
};

#endif // DIGITAL_IO_HPP