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
#include "Watchdog_t4.h"
#include "messages.pb.h"
#include "imu.hpp"
#include "analog_io.hpp"
#include "digital_io.hpp"
#include "memory_if.hpp"
#include "space_computer.hpp"
#include "donwlink_message.hpp"
#include "pins.hpp"


#define INIT_ATTEMPTS 3
#define SAMP_DELAY 1000
#define WD_ALERT_MS 10000

void WDOG_Setup();
void wdog1_feed();

IMU Imu;
memory_if memIf;
analog_io analogIo;
digital_io digitalIo;
space_computer spaceComp;

WDT_T4<WDT1> dog;

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

  WDT_timings_t config;
  config.trigger = 5;
  config.timeout = 10;
  dog.begin(config);
 

}//*/

/**
 * @brief main program loop
 * 
 */
void loop()
{
  downlink_proto_SystemMetrics packet;
  DownlinkMessage msg;
  bool valid;

  while (1)
  {
    packet = Imu.read(packet);
    packet = digitalIo.read(packet);
    packet = analogIo.read(packet);
    packet = spaceComp.read(packet, 1);

    // send or store packet
    if (Serial)
    {
      msg = DownlinkMessage(packet);
      uint16_t packet_length = msg.packetLength();
      uint8_t *packet = new uint8_t[packet_length];
      msg.packet(packet, packet_length);
      Serial.write(packet, packet_length);
      delete[] packet;
    }
    else
    {
      memIf.write(packet);
    }

    delay(SAMP_DELAY);
    dog.feed();
  }
}
