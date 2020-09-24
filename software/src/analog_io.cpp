/**
 * @file analog_io.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "analog_io.hpp"
#include <Arduino.h>

/* Private Methods */

float analog_io::convert_temp(uint16_t raw)
{
    return 0.0;
}

float analog_io::convert_voltage(uint16_t raw)
{
    // voltage dividers are balanced
    float pinVoltage = VREF * (float(raw) / MAX_ADC_VAL);
    return (pinVoltage * 2);
}

/* Public Methods */

bool analog_io::init()
{
    Serial.println("Analog I/O bank object initialized...");
    analogReadResolution(ADC_PREC);
    analogReference(0);
    pinMode(V_0, INPUT);
    pinMode(V_1, INPUT);
    pinMode(T_0, INPUT);
    pinMode(T_1, INPUT);
    pinMode(A_0, INPUT);
    pinMode(A_1, INPUT);
    pinMode(A_2, INPUT);
    pinMode(A_3, INPUT); 

    MAX_ADC_VAL = pow(2,ADC_PREC) - 1;   
    return true;
}

bool analog_io::read(Data *data)
{
    uint16_t v0_raw = analogRead(V_0);
    uint16_t v1_raw = analogRead(V_1);
    uint16_t t0_raw = analogRead(T_0);
    uint16_t t1_raw = analogRead(T_1);
    uint16_t a0_raw = analogRead(A_0);
    uint16_t a1_raw = analogRead(A_1);
    uint16_t a2_raw = analogRead(A_2);
    uint16_t a3_raw = analogRead(A_3);

    data->analogData.v0 = convert_voltage(v0_raw);
    data->analogData.v1 = convert_voltage(v1_raw);
    //data->analogData.temp0 = convert_temp(t0_raw);
    //data->analogData.temp1 = convert_temp(t1_raw);
    // just for analog tests
    data->analogData.temp0 = convert_voltage(t0_raw);
    data->analogData.temp1 = convert_voltage(t1_raw);

    data->analogData.a0 = convert_voltage(a0_raw);
    data->analogData.a1 = convert_voltage(a1_raw);
    data->analogData.a2 = convert_voltage(a2_raw);
    data->analogData.a3 = convert_voltage(a3_raw);    

    return true;
}