/**
 * @file pins.hpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief pin definitions for flight-unit
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PINS_HPP
#define PINS_HPP

// Discrete Digital
#define SC_D0 0
#define SC_D1 1
#define SC_D2 2
#define SC_D3 3
#define SC_D4 4

// Discrete Analog
#define A_0 20
#define A_1 21
#define A_2 22
#define A_3 23

// Debug LEDs
#define LED_0 5
#define LED_1 6
#define LED_2 7

// Analog Voltages
#define V_0 16
#define V_1 17

// Analog Temperatures
#define T_0 14
#define T_1 15

// IIC
#define IIC_SCL 19
#define IIC_SDA 18

// SPI
#define MEM_CS0  8
#define MEM_CS1  9
#define MEM_CS2  10
#define MEM_MOSI 11
#define MEM_MISO 12
#define MEM_SCK  13

#endif // PINS_HPP