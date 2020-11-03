/**
 * @file memory_if.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "memory_if.hpp"
#include <Arduino.h>

/****** Private Methods ******/
uint8_t memory_if::majority_voter(downlink_proto_SystemMetrics d1, downlink_proto_SystemMetrics d2, downlink_proto_SystemMetrics d3)
{
    return 1;
}

bool memory_if::ecc_check(downlink_proto_SystemMetrics data)
{
    return true;
}

/***** Public Methods ******/

memory_if::memory_if()
{
    #if DEBUG
        Serial.println("constructing memory interface");
    #endif

    devices = new fram[3];
}

memory_if::~memory_if()
{
    delete[] devices;
}

bool memory_if::init()
{
    #if DEBUG
        Serial.println("Memory interface initialized...");
    #endif
    return true;
}

bool memory_if::write(downlink_proto_SystemMetrics data)
{
    return true;
}

bool memory_if::read(downlink_proto_SystemMetrics *data)
{
    #if DEBUG
        Serial.println("Reading packet from memory...");
    #endif
    return true;
}
