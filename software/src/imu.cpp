/**
 * @file IMU.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "imu.hpp"

IMU::IMU()
{
    enabled = true;
    device = Adafruit_BNO055(55, 0x28);
    delay(1000);
}

IMU::~IMU()
{

}

bool IMU::init()
{
    #if DEBUG
        Serial.println("Initializing IMU...");
    #endif 
    
    
    if (device.begin())
    {
        Serial.println("success = true");
        enabled = true;
        return true;
    }
    else
    {
        Serial.println("success = false");
        enabled = false;
        return false;
    }
}

downlink_proto_SystemMetrics IMU::read(downlink_proto_SystemMetrics data)
{
    if (!enabled)
    {
        return data;
    }

    #if DEBUG
        Serial.println("Reading IMU data...");
    #endif

    sensors_event_t event;
    device.getEvent(&event);
    quat = device.getQuat();
    magnet = device.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    omega = device.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    linearAccel = device.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

    data.imu.euler_x = event.orientation.x;
    data.imu.euler_y = event.orientation.y;
    data.imu.euler_z = event.orientation.z;

    data.imu.quat_a = quat.w();
    data.imu.quat_b = quat.x();
    data.imu.quat_c = quat.y();
    data.imu.quat_d = quat.z();
    data.imu.omega_x = omega.x();
    data.imu.omega_y = omega.y();
    data.imu.omega_z = omega.z();
    data.imu.linearAccel_x = linearAccel.x();
    data.imu.linearAccel_y = linearAccel.y();
    data.imu.linearAccel_z = linearAccel.z();
    data.imu.mag_x = magnet.x();
    data.imu.mag_y = magnet.y();
    data.imu.mag_z = magnet.z();

    int8_t temp = device.getTemp();
    data.imu.temperature = temp;

    data.has_imu = true;

    return data;
}

bool IMU::enable()
{
    #if DEBUG
        Serial.println("Enabling IMU ...");
    #endif

    enabled = true;
    return true;
}

bool IMU::disable()
{
    #if DEBUG
        Serial.println("Disabling IMU...");
    #endif
    enabled = false;
    return true;
}