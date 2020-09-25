/**
 * @file digital_io.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "digital_io.hpp"
#include <Arduino.h>

bool digital_io::init()
{
    Serial.println("digital I/O bank initialized...");
    return true;
}

bool digital_io::read(Data *data)
{
    Serial.println("Reading discrete digital i/o...");
    return true;
}

bool digital_io::write_led(uint8_t led, ledCode code)
{
    return true;
}
