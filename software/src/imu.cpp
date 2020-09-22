/**
 * @file IMU.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "IMU.hpp"

bool IMU::init()
{
    Serial.println("Initializing IMU...");
    return true;
}

bool IMU::read(Data *data)
{
    return true;
}

bool IMU::enable()
{
    return true;
}

bool IMU::disable()
{
    return true;
}