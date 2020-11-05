#ifndef IMU_HPP
#define IMU_HPP

#include <Wire.h>
#include <Adafruit_BNO055.h>
#include "pins.hpp"
#include "messages.pb.h"

class IMU
{
private:
    Adafruit_BNO055 device;
    sensors_event_t  event;
    imu::Quaternion quat;
    imu::Vector<3> magnet;
    bool enabled;

    // TODO: add any helper vars here
public:
    IMU();
    ~IMU();
    bool init();
    downlink_proto_SystemMetrics read(downlink_proto_SystemMetrics data);
    bool enable();
    bool disable();

};

#endif // IMU_HPP