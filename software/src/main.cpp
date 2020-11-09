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
  bool IMU_INT = false;
  bool ANALOG_INT = false;
  bool DIGITAL_INT = false;
  bool SPACECOMP_INT = false;
  bool MEMIF_INT = false;

  Serial.begin(115200);
  #if DEBUG
    while (!Serial)
      delay(10);
    Serial.println("Starting up");
  #endif
  
  
  while (IMU_INT == false || ANALOG_INT==false || DIGITAL_INT==false || SPACECOMP_INT==false || MEMIF_INT==false){
    uint8_t cnt = 1;
    while (!Imu.init() && cnt <= INIT_ATTEMPTS)
    {
      Serial.println("IMU DID NOT INIT");
      digitalIo.write_led(CODE1);
      if(Imu.init() == true){
        IMU_INT = true;
      }
      cnt++;
    }
    
    cnt = 1;
    while (!memIf.init() && cnt <= INIT_ATTEMPTS)
    {
      Serial.println("MEMORY INTERFACE DID NOT INIT");
      digitalIo.write_led(CODE2);
      if(memIf.init()==true){
        MEMIF_INT = true;
      }
      cnt++;
    }
    
    cnt = 1;
    while (!analogIo.init() && cnt <= INIT_ATTEMPTS)
    {
      Serial.println("ANALOG IO DID NOT INIT");
      digitalIo.write_led(CODE3);
      if(analogIo.init() == true){
        ANALOG_INT = true;
      }
      cnt++;
      

    }

    cnt = 1;
    while (!digitalIo.init() && cnt <= INIT_ATTEMPTS)
    {
      Serial.println("DIGITAL IO DID NOT INIT");
      digitalIo.write_led(CODE4);
      if(digitalIo.init()==true){
        DIGITAL_INT = true;
      }
      cnt++;
      
    }

    cnt = 1;
    while (!spaceComp.init() && cnt <= INIT_ATTEMPTS)
    {
      Serial.println("SPACE COMPUTER DID NOT INTI");
      digitalIo.write_led(CODE5);
      if(spaceComp.init()==true){
        SPACECOMP_INT = true;
      }
      cnt++;
      
    }

  }

  WDT_timings_t config;
  config.trigger = 5;
  config.timeout = 10;
  dog.begin(config);
 

}

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
