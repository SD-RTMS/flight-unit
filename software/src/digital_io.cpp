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

    data.has_digital = true;

    return data;
}

bool digital_io::write_led(ledCode code)
{
    #if DEBUG
        Serial.println("writing LED code");
    #endif

    if (code == CODE1){ //001  --- IMU
        digitalWrite(LED_0, HIGH);
        delay(500);
        digitalWrite(LED_0, LOW);
        delay(100);
        //Serial.println("IMU LIGHT");

    }
    
    if (code == CODE2){ //010   MEMORY IF
        digitalWrite(LED_1,HIGH);
        delay(500);
        digitalWrite(LED_1, LOW);
        delay(100);
        //Serial.println("MEM LIGHT");
    }
    if (code == CODE3){ //011 ANALOG 
        digitalWrite(LED_0, HIGH);
        digitalWrite(LED_1, HIGH);
        delay(500);
        digitalWrite(LED_0, LOW);
        digitalWrite(LED_1, LOW);
        delay(100);
        //Serial.println("ANALOG LIGHT");
    }
    if (code == CODE4){ //100 DIGITAL
        digitalWrite(LED_2, HIGH);
        delay(500);
        digitalWrite(LED_2, LOW);
        delay(100);
        //Serial.println("DIGITAL LIGHT");

    }
    if (code == CODE5){ //101 SPACE COMP
        digitalWrite(LED_0,HIGH);
        digitalWrite(LED_2,HIGH);
        delay(500);
        digitalWrite(LED_0, LOW);
        digitalWrite(LED_2, LOW);
        delay(100);
        //Serial.println("SPACE COMP LIGHT");
    }

    
        


    return true;
}
