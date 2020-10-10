/**
 * @file mem.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "fram.hpp"
#include <SPI.h>


/***** Private Methods *****/
bool fram::write8(uint32_t addr, byte val)
{
    mem.writeEnable(true);
    mem.write8(addr, val);
    mem.writeEnable(false);

    return true;
}

bool fram::write16(uint32_t addr, int16_t val)
{
    byte b1 = (byte)(val >> 8);
    byte b2 = (byte)val;

    write8(addr, b1);
    write8(addr + 1, b2);

    return true;
}

bool fram::writeF32(uint32_t addr, float val)
{
    int16_t hw1 = (int16_t)val;
    int16_t hw2 = (int16_t)((65536)*(val - hw1));

    write16(addr,hw1);
    write16(addr + 2, hw2);

    return true;
}

int8_t fram::read8(uint32_t addr)
{
    return (int8_t)(mem.read8(addr));
}

int16_t fram::read16(uint32_t addr)
{
    byte b1 = (byte)mem.read8(addr);
    byte b2 = (byte)mem.read8(addr + 1);

    return (int16_t)((b1 << 8) + b2);
}

float fram::readF32(uint32_t addr)
{
    uint16_t hw1 = read16(addr);
    uint16_t hw2 = read16(addr + 2);

    return (float)(hw1 + hw2/65536.0);
}


/***** Public Methods *****/

bool fram::init(int8_t select, uint8_t addr_size)
{
    cs = select;

    // create software SPI object
    mem = Adafruit_FRAM_SPI((int8_t)MEM_SCK, (int8_t)MEM_MISO, (int8_t)MEM_MOSI, cs);

    // start fram
    if (mem.begin(addr_size))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool fram::read(Data *data, uint32_t addr)
{
    // read analog IO data
    data->analogData.temp0 = readF32(addr);
    data->analogData.temp1 = readF32(addr + 4);
    data->analogData.v0 = read16(addr + 8);
    data->analogData.v1 = read16(addr + 10);
    data->analogData.a0 = read16(addr + 12);
    data->analogData.a1 = read16(addr + 14);
    data->analogData.a2 = read16(addr + 16);
    data->analogData.a3 = read16(addr + 18);

    // read digital IO data
    data->digitalData.d0 = (bool)read8(addr + 20);
    data->digitalData.d1 = (bool)read8(addr + 21);
    data->digitalData.d2 = (bool)read8(addr + 22);
    data->digitalData.d3 = (bool)read8(addr + 23);
    data->digitalData.d4 = (bool)read8(addr + 24);

    // read imu data
    data->imuData.eulerX = readF32(addr + 25);
    data->imuData.eulerY = readF32(addr + 29);
    data->imuData.eulerZ = readF32(addr + 33);
    data->imuData.quatA =  readF32(addr + 37);
    data->imuData.quatB =  readF32(addr + 41);
    data->imuData.quatC =  readF32(addr + 45);
    data->imuData.quatD =  readF32(addr + 49);
    data->imuData.omegaX = readF32(addr + 53);
    data->imuData.omegaY = readF32(addr + 57);
    data->imuData.omegaZ = readF32(addr + 61);
    data->imuData.magX =   readF32(addr + 65);
    data->imuData.magY =   readF32(addr + 69);
    data->imuData.magZ =   readF32(addr + 73);
    data->imuData.temp =   readF32(addr + 77);

    data->scData.current = readF32(addr + 81);
    data->scData.zynqV = readF32(addr + 85);
    data->scData.dieTemp = readF32(addr + 89);

    return true;
}

bool fram::write(Data data, uint32_t addr)
{
    // write analog IO data
    writeF32(addr, data.analogData.temp0);
    writeF32(addr + 4, data.analogData.temp1);
    write16(addr + 8, data.analogData.v0);
    write16(addr + 10, data.analogData.v1);
    write16(addr + 12, data.analogData.a0);    
    write16(addr + 14, data.analogData.a1);
    write16(addr + 16, data.analogData.a2);
    write16(addr + 18, data.analogData.a3);

    // write digital IO data
    write8(addr + 20, (byte)data.digitalData.d0);
    write8(addr + 21, (byte)data.digitalData.d1);
    write8(addr + 22, (byte)data.digitalData.d2);
    write8(addr + 23, (byte)data.digitalData.d3);
    write8(addr + 24, (byte)data.digitalData.d4);

    // IMU Data
    writeF32(addr + 25, data.imuData.eulerX);
    writeF32(addr + 29, data.imuData.eulerY);
    writeF32(addr + 33, data.imuData.eulerZ);
    writeF32(addr + 37, data.imuData.quatA);
    writeF32(addr + 41, data.imuData.quatB);
    writeF32(addr + 45, data.imuData.quatC);
    writeF32(addr + 49, data.imuData.quatD);
    writeF32(addr + 53, data.imuData.omegaX);
    writeF32(addr + 57, data.imuData.omegaY);
    writeF32(addr + 61, data.imuData.omegaZ);
    writeF32(addr + 65, data.imuData.magX); 
    writeF32(addr + 69, data.imuData.magY);
    writeF32(addr + 73, data.imuData.magZ);
    writeF32(addr + 77, data.imuData.temp);   

    writeF32(addr + 81, data.scData.current);
    writeF32(addr + 85, data.scData.zynqV);
    writeF32(addr + 89, data.scData.dieTemp);

    return true;
}