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
bool memory_if::majority_voter(DownlinkMessage &cor, DownlinkMessage d1, DownlinkMessage d2, DownlinkMessage d3)
{
    bool chk1 = d1.validateChecksum();
    bool chk2 = d2.validateChecksum();
    bool chk3 = d3.validateChecksum();
    bool match12 = ((d1.checksum()) == d2.checksum());
    bool match13 = ((d1.checksum()) == d3.checksum());
    bool match23 = ((d2.checksum()) == d3.checksum());
    bool allMatch = (match12 && match13 && match23);
    bool allChk = (chk1 && chk2 && chk3);

    if (allChk && allMatch)
    { 
      cor = d1;
      return true;
    }
    else
    {
        if (chk1 && chk2 && match12)
        {
            cor = d1;
            return true;
        }
        else if (chk1 && chk3 && match13)
        {
            cor = d1;
            return true;
        }
        else if (chk2 && chk3 && match23)
        {
            cor = d2;
            return true;
        }
        else
        {
            #if DEBUG
                Serial.println("Unrecoverable Error in packet");
            #endif
            return false;
        }
    }
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

    device1 = fram(MEM_CS0);
    device2 = fram(MEM_CS1);
    device3 = fram(MEM_CS2);
}

memory_if::~memory_if()
{
}

bool memory_if::init()
{
    #if DEBUG
        Serial.println("Memory interface initialized...");
    #endif

    bool success = device1.init() && device2.init() && device3.init();

    return success;
}

bool memory_if::write(downlink_proto_SystemMetrics data)
{
    #if DEBUG
        Serial.println("writing packet to memory");
    #endif

    // write all data to each fram
    bool full1 = !device1.write(data);
    bool full2 = !device2.write(data);
    bool full3 = !device3.write(data);

    if (full1 && full2 && full3)
    {
        // all are full need to remap to duplex
        return false; //eventually change to true
    }
    else if (!full1 && !full2 && !full3)
    {
        //every thing is good to go 
        return true;
    }
    else
    {
        //weird case handle later
        return false;
    }

}

bool memory_if::read(DownlinkMessage &returnMsg)
{
    #if DEBUG
        Serial.println("Reading packet from memory...");
    #endif

    // read each fram module
    DownlinkMessage msg1 = device1.read();
    DownlinkMessage msg2 = device2.read();
    DownlinkMessage msg3 = device3.read();

    // select majority packet
    DownlinkMessage correctMsg;
    bool valid = majority_voter(correctMsg, msg1, msg2, msg3);
    if (valid)
    {
        returnMsg = correctMsg;
        return true;
    }
    else
    {
        return false;
    }
}
