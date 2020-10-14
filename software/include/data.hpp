/**
 * @file data.hpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef DATA_HPP
#define DATA_HPP

#include <pb_encode.h>

#include <inttypes.h>

/**
 * @brief Analog I/O bank data type
 * 
 */
typedef struct analogIoData
{
    float temp0;
    float temp1;
    uint16_t v0;
    uint16_t v1;
    uint16_t a0;
    uint16_t a1;
    uint16_t a2;
    uint16_t a3;
} analogIoData;

/**
 * @brief Digital I/O bank data type
 * 
 */
typedef struct digitalIoData
{
    bool d0;
    bool d1;
    bool d2;
    bool d3;
    bool d4;

} digitalIoData;

/**
 * @brief Space computer data type
 * 
 */
typedef struct ScData
{
    float current;
    float zynqV;
    float dieTemp;
} ScData;

/**
 * @brief IMU data type
 * 
 */
typedef struct ImuData
{
    float eulerX;
    float eulerY;
    float eulerZ;
    float quatA;
    float quatB;
    float quatC;
    float quatD;
    float omegaX;
    float omegaY;
    float omegaZ;
    float magX;
    float magY;
    float magZ;
    float temp;
} ImuData;

/**
 * @brief Master data type for all sensors
 * 
 */
typedef struct Data
{
    analogIoData  analogData;
    digitalIoData digitalData;
    ImuData       imuData;
    ScData        scData;
} Data;

#endif // DATA_HPP