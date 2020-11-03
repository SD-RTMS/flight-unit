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

#include "imu.hpp"

bool IMU::init()
{
    #if DEBUG
        Serial.println("Initializing IMU...");
    #endif 

    // TODO: initialize imu here

    return true;
}

bool IMU::read(downlink_proto_SystemMetrics *data)
{
    #if DEBUG
        Serial.println("Reading IMU data...");
    #endif

    return true;
}

bool IMU::enable()
{
    #if DEBUG
        Serial.println("Enabling IMU ...");
    #endif

    return true;
}

bool IMU::disable()
{
    #if DEBUG
        Serial.println("Disabling IMU...");
    #endif

    return true;
}