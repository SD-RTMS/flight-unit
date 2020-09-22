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
#include "Imu.hpp"
#include "analog_io.hpp"
#include "digital_io.hpp"
#include "memory_if.hpp"
#include "space_computer.hpp"

#define INIT_ATTEMPTS 3
#define SAMP_DELAY    5

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

}

/**
 * @brief main program loop
 * 
 */
void loop() {
  // Dummy function to begin polling functions and sending data
  Data *packet = new Data;

  Serial.println("Reading IMU...");
  Imu.read(packet);
  Serial.println("Reading digital I/O bank...");
  digitalIo.read(packet);
  Serial.println("Reading analog I/O bank...");
  analogIo.read(packet);
  Serial.println("Reading Space Computer interface..");
  spaceComp.read(packet,1);
  Serial.println("Writing to memory...");
  memIf.write(*packet);

  delay(1);
  while (!Serial.available()){}
  Serial.println("Reading Memory interface...");

  delay(SAMP_DELAY);
}