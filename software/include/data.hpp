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

/**
 * @brief Analog I/O bank data type
 * 
 */
typedef struct analogIoData
{
    float temp0;
    float temp1;
    float v0;
    float v1;
    float a0;
    float a1;
    float a2;
    float a3;
} analogIoData;

/**
 * @brief Digital I/O bank data type
 * 
 */
typedef struct digitalIoData
{
    float d0;
    float d1;
    float d2;
    float d3;
    float d4;

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