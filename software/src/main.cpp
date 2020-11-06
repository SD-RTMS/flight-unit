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
#include "donwlink_message.hpp"

#define INIT_ATTEMPTS 3
#define SAMP_DELAY 1000
#define DEBUG true

IMU Imu;
memory_if memIf;
analog_io analogIo;
digital_io digitalIo;
space_computer spaceComp;

downlink_proto_SystemMetrics packet;
DownlinkMessage msg;

    /**
 * @brief Setup function run on startup
 * 
 */
    void
    setup()
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
    memIf.write(packet);
    msg = memIf.read();
    
    delay(SAMP_DELAY);
}
