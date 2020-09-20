/**
 * @file analog_io.hpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef ANALOG_IO_HPP
#define ANALOG_IO_HPP

#include "pins.hpp"
#include "data.hpp"
#include <inttypes.h>

/**
 * @brief digital i/o bank class
 * 
 */
class analog_io
{
private:
    const uint8_t bank[5] = {SC_D0, SC_D1, SC_D2, SC_D3, SC_D4};
    const int BETA = 2900; //TODO: get exact value
    const int ADC_PREC = 12;
    const float VREF = 3.3;

    /**
     * @brief converts analog reading to temperature
     * 
     * @return float - temperature in degrees C
     */
    float convert_temp(uint16_t);

    /**
     * @brief converts analog reading to voltage
     * 
     * @return float 
     */
    float convert_voltage(uint16_t);

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

};

#endif // ANALOG_IO_HPP