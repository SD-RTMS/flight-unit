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

bool fram::read(Data *data)
{
    return true;
}

bool fram::write(Data data)
{
    return true;
}