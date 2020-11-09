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
#include "RTClib.h"
#include <TimeLib.h>


#define INIT_ATTEMPTS 3
#define SAMP_DELAY 5000
#define WD_ALERT_MS 10000
#define TIME_HEADER "T" 

void printPacket(downlink_proto_SystemMetrics packet);
time_t getTeensy3Time(); 
unsigned long processSyncMessage();

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
      //Serial.println("IMU DID NOT INIT");
      digitalIo.write_led(CODE1);
      cnt++;
    }
    
    cnt = 1;
    while (!memIf.init() && cnt <= INIT_ATTEMPTS)
    {
      //Serial.println("MEMORY INTERFACE DID NOT INIT");
      digitalIo.write_led(CODE2);
      cnt++;
    }
    
    cnt = 1;
    while (!analogIo.init() && cnt <= INIT_ATTEMPTS)
    {
      //Serial.println("ANALOG IO DID NOT INIT");
      digitalIo.write_led(CODE3);
      cnt++;
    }

    cnt = 1;
    while (!digitalIo.init() && cnt <= INIT_ATTEMPTS)
    {
      //Serial.println("DIGITAL IO DID NOT INIT");
      digitalIo.write_led(CODE4);
      cnt++; 
    }

    cnt = 1;
    while (!spaceComp.init() && cnt <= INIT_ATTEMPTS)
    {
      //Serial.println("SPACE COMPUTER DID NOT INTI");
      digitalIo.write_led(CODE5);
      cnt++;
    }

  WDT_timings_t config;
  config.trigger = 5;
  config.timeout = 10;
  dog.begin(config);

  setSyncProvider(getTeensy3Time);
  time_t t = processSyncMessage();
  if (t != 0)
  {
    Teensy3Clock.set(t); // set the RTC
    setTime(t);
  }

}

/**
 * @brief main program loop
 * 
 */
void loop()
{
  downlink_proto_SystemMetrics packet = downlink_proto_SystemMetrics_init_zero;
  DownlinkMessage msg;
  bool valid;

  while (1)
  {
    //Reset Packet Has
    packet.has_analog = false;
    packet.has_computer = false;
    packet.has_digital = false;
    packet.has_imu = false;
    packet.has_power_supply = false;
    packet.has_time = false;

    packet = Imu.read(packet);
    packet = digitalIo.read(packet);
    packet = analogIo.read(packet);
    packet = spaceComp.read(packet, 1);

    // add timestamp
    packet.time.year = year();
    packet.time.month = month();
    packet.time.day = day();
    packet.time.hour = hour();
    packet.time.minute = minute();
    packet.time.second = second();
    packet.has_time = true;

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

    #if DEBUG
      printPacket(packet);
    #endif

    delay(SAMP_DELAY);
    dog.feed();
  }
}

void printPacket(downlink_proto_SystemMetrics packet)
{
  Serial.printf("\nhas time: %d\n", packet.has_time);
  Serial.printf("month: %d\n", packet.time.month);
  Serial.printf("day: %d\n", packet.time.day);
  Serial.printf("year: %d\n", packet.time.year);
  Serial.printf("hour: %d\n", packet.time.hour);
  Serial.printf("minute: %d\n", packet.time.minute);
  Serial.printf("second: %d\n\n", packet.time.second);

  Serial.printf("has power supply: %d\n", packet.has_power_supply);
  Serial.printf("temperature_v0: %f\n", packet.power_supply.temperature_v0);
  Serial.printf("temperature_v1: %f\n", packet.power_supply.temperature_v1);
  Serial.printf("level_3v3: %f\n", packet.power_supply.level_3v3);
  Serial.printf("level_5v0: %f\n\n", packet.power_supply.level_5v0);

  Serial.printf("has computer: %d\n", packet.has_computer);
  Serial.printf("power_voltage: %f\n", packet.computer.power_voltage);
  Serial.printf("power_current: %f\n", packet.computer.power_current);
  Serial.printf("temperature_die: %f\n\n", packet.computer.temperature_die);

  Serial.printf("has imu: %d\n", packet.has_imu);
  Serial.printf("euler_x: %f\n", packet.imu.euler_x);
  Serial.printf("euler_y: %f\n", packet.imu.euler_y);
  Serial.printf("euler_z: %f\n", packet.imu.euler_z);
  Serial.printf("quat_a: %f\n", packet.imu.quat_a);
  Serial.printf("quat_b: %f\n", packet.imu.quat_b);
  Serial.printf("quat_c: %f\n", packet.imu.quat_c);
  Serial.printf("quat_d: %f\n", packet.imu.quat_d);
  Serial.printf("linearAccel_x: %f\n", packet.imu.linearAccel_x);
  Serial.printf("linearAccel_y: %f\n", packet.imu.linearAccel_y);
  Serial.printf("linearAccel_z: %f\n", packet.imu.linearAccel_z);
  Serial.printf("omega_x: %f\n", packet.imu.omega_x);
  Serial.printf("omega_y: %f\n", packet.imu.omega_y);
  Serial.printf("omega_z: %f\n", packet.imu.omega_z);
  Serial.printf("magnitude_x: %f\n", packet.imu.magnitude_x);
  Serial.printf("magnitude_y: %f\n", packet.imu.magnitude_y);
  Serial.printf("magnitude_z: %f\n", packet.imu.magnitude_z);
  Serial.printf("temperature: %f\n\n", packet.imu.temperature);

  Serial.printf("has digital: %d\n", packet.has_digital);
  Serial.printf("digital_0: %d\n", packet.digital.digital_0);
  Serial.printf("digital_1: %d\n", packet.digital.digital_1);
  Serial.printf("digital_2: %d\n", packet.digital.digital_2);
  Serial.printf("digital_3: %d\n", packet.digital.digital_3);
  Serial.printf("digital_4: %d\n\n", packet.digital.digital_4);

  Serial.printf("has analog: %d\n", packet.has_analog);
  Serial.printf("analog_0: %f\n", packet.analog.analog_0);
  Serial.printf("analog_1: %f\n", packet.analog.analog_1);
  Serial.printf("analog_2: %f\n", packet.analog.analog_2);
  Serial.printf("analog_3: %f\n\n", packet.analog.analog_3);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

unsigned long processSyncMessage()
{
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if (Serial.find(TIME_HEADER))
  {
    pctime = Serial.parseInt();
    return pctime;
    if (pctime < DEFAULT_TIME)
    {              // check the value is a valid time (greater than Jan 1 2013)
      pctime = 0L; // return 0 to indicate that the time is not valid
    }
  }
  return pctime;
}