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

#include <Arduino.h>
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
#define SAMP_DELAY 5000

IMU Imu;
memory_if memIf;
analog_io analogIo;
digital_io digitalIo;
space_computer spaceComp;

/**
 * @brief Setup function run on startup
 * 
 */
void setup()
{
  
  uint8_t cnt = 1;
  while (!Imu.init() && cnt <= INIT_ATTEMPTS)
  {
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
  #if DEBUG
    Serial.println("Initialization done, entering main loop...\n");
  #endif
  downlink_proto_SystemMetrics *packet = new downlink_proto_SystemMetrics;

  // sensor polling loop
  while (1)
  {
    Imu.read(packet);
    digitalIo.read(packet);
    analogIo.read(packet);
    spaceComp.read(packet, 1);
    memIf.write(*packet);
    memIf.read(packet);

    Serial.println("\n");
    delay(SAMP_DELAY);
  }
}
