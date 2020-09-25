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
uint8_t memory_if::majority_voter(Data d1, Data d2, Data d3)
{
    return 1;
}

bool memory_if::ecc_check(Data)
{
    return true;
}

/***** Public Methods ******/

memory_if::memory_if()
{
    devices = new fram[3];
}

memory_if::~memory_if()
{
    delete[] devices;
}

bool memory_if::init()
{
    Serial.println("Memory interface initialized...");
    return true;
}

bool memory_if::write(Data data)
{
    return true;
}

bool memory_if::read(Data *)
{
    Serial.println("Reading packet from memory...");
    return true;
}

