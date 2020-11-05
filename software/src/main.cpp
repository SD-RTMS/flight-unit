/**
 * @file main.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Arduino.h"
#include "messages.pb.h"
#include "imu.hpp"
#include "analog_io.hpp"
#include "digital_io.hpp"
#include "memory_if.hpp"
#include "space_computer.hpp"

// TODO: come up with a less hacky fix for this

extern "C"
{
  int __exidx_start() { return -1; }
  int __exidx_end() { return -1; }
}

#define INIT_ATTEMPTS 3
#define SAMP_DELAY 1000
#define DEBUG true

IMU Imu;
memory_if memIf;
analog_io analogIo;
digital_io digitalIo;
space_computer spaceComp;

downlink_proto_SystemMetrics packet;

/**
 * @brief Setup function run on startup
 * 
 */
void setup()
{
  
  Serial.begin(115200);
  #if DEBUG
    while (!Serial)
      delay(10);
    Serial.println("Starting up");
  #endif
  
  uint8_t cnt = 1;
  while (!Imu.init() && cnt <= INIT_ATTEMPTS)
  {
    Serial.println("IMU DID NOT INIT");
    delayMicroseconds(100);
    cnt++;
  }
  
  cnt = 1;
  while (!memIf.init() && cnt <= INIT_ATTEMPTS)
  {
    delayMicroseconds(100);
    cnt++;
  }
  
  cnt = 1;
  while (!analogIo.init() && cnt <= INIT_ATTEMPTS)
  {
    delayMicroseconds(100);
    cnt++;
  }

  cnt = 1;
  while (!digitalIo.init() && cnt <= INIT_ATTEMPTS)
  {
    delayMicroseconds(100);
    cnt++;
  }

  cnt = 1;
  while (!spaceComp.init() && cnt <= INIT_ATTEMPTS)
  {
    delayMicroseconds(100);
    cnt++;
  }
  
}//*/

/**
 * @brief main program loop
 * 
 */
void loop()
{    
    packet = Imu.read(packet);
    packet = digitalIo.read(packet);
    packet = analogIo.read(packet);
    packet = spaceComp.read(packet, 1);
    //memIf.write(*packet);
    //memIf.read(packet);

    Serial.println("Euler Vectors");
    Serial.print("X: ");
    Serial.print(packet.imu.euler_x);
    Serial.print("\tY: ");
    Serial.print(packet.imu.euler_y);
    Serial.print("\tZ: ");
    Serial.println(packet.imu.euler_z);
    Serial.println("");
    Serial.println(packet.imu.temperature);
    
    delay(SAMP_DELAY);

}
