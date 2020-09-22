/**
 * @file analog_io.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "analog_io.hpp"
#include <Arduino.h>

/* Private Methods */

float analog_io::convert_temp(uint16_t raw)
{
    return 0.0;
}

float analog_io::convert_voltage(uint16_t raw)
{
    return 0.0;
}

/* Public Methods */

bool analog_io::init()
{
    Serial.println("Analog I/O bank object initialized...");
    return true;
}

bool analog_io::read(Data *data)
{
    return true;
}