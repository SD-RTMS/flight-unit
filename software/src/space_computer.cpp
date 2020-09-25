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
    Serial.println("Initializing SC interface...");
    return true;
}

bool space_computer::read(Data *data, uint8_t msgType)
{
    Serial.println("Reading from space computer...");
    return true;
}