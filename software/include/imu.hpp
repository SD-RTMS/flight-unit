#ifndef IMU_HPP
#define IMU_HPP

#include <Wire.h>
#include <Adafruit_BNO055.h>
#include "pins.hpp"
#include "data.hpp"

class IMU
{
private:
    Adafruit_BNO055 device;
    sensors_event_t event;
    bool debug;
    
    // TODO: add any helper vars here
public:
    bool init();
    bool read(Data *);
    bool enable();
    bool disable();

};

#endif // IMU_HPP