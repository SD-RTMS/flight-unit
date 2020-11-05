/**
 * @file space_computer.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "space_computer.hpp"

bool space_computer::init()
{
    #if DEBUG
        Serial.println("Initializing SC interface...");
    #endif
    
    return true;
}

downlink_proto_SystemMetrics space_computer::read(downlink_proto_SystemMetrics data, uint8_t msgType)
{
    #if DEBUG
        Serial.println("Reading from space computer...");
    #endif

    return data;
}