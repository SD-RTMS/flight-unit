/**
 * @file digital_io.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "digital_io.hpp"
#include <Arduino.h>

bool digital_io::init()
{
    #if DEBUG
        Serial.println("digital I/O bank initialized...");
    #endif

    // digital inputs
    pinMode(SC_D0, INPUT);
    pinMode(SC_D1, INPUT);
    pinMode(SC_D2, INPUT);
    pinMode(SC_D3, INPUT);
    pinMode(SC_D4, INPUT);

    // digital outputs (LEDs)
    pinMode(LED_0, OUTPUT);
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);

    return true;
}

downlink_proto_SystemMetrics digital_io::read(downlink_proto_SystemMetrics data)
{
    #if DEBUG
        Serial.println("Reading discrete digital i/o...");
    #endif

    data.digital.digital_0 = digitalRead(SC_D0);
    data.digital.digital_1 = digitalRead(SC_D1);
    data.digital.digital_2 = digitalRead(SC_D2);
    data.digital.digital_3 = digitalRead(SC_D3);
    data.digital.digital_4 = digitalRead(SC_D4);

    return data;
}

bool digital_io::write_led(uint8_t led, ledCode code)
{
    #if DEBUG
        Serial.println("writing LED code");
    #endif

    return true;
}
