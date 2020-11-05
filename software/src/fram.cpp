/**
 * @file fram.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "fram.hpp"

/***** Private Methods *****/

bool fram::write_byte(uint8_t byte)
{
    return true;
}

uint8_t fram::read_byte()
{
    return 0;
}

/***** Public Methods *****/

bool fram::init(uint8_t select)
{
    cs = select;
    return true;
}

downlink_proto_SystemMetrics fram::read(downlink_proto_SystemMetrics data)
{
    return data;
}

bool fram::write(downlink_proto_SystemMetrics data)
{
    return true;
}