

#ifndef FRAM_HPP
#define FRAM_HPP

#include "pins.hpp"
#include "data.hpp"
#include "Adafruit_FRAM_SPI.h"
#include <inttypes.h>

class fram
{
private:
    uint8_t cs;
    Adafruit_FRAM_SPI mem;

    bool write8(uint32_t addr, byte val);
    bool write16(uint32_t addr, int16_t val);
    bool writeF32(uint32_t addr, float val);

    int8_t read8(uint32_t addr);
    int16_t read16(uint32_t addr);
    float readF32(uint32_t addr);

public:
    
    /**
     * @brief initializes the fram module
     * 
     * @return true 
     * @return false 
     */
    bool init(int8_t, uint8_t);

    /**
     * @brief reads the data packet from the fram module
     * 
     * @return true 
     * @return false 
     */
    bool read(Data *, uint32_t);

    /**
     * @brief writes the packet to the fram module
     * 
     * @return true 
     * @return false 
     */
    bool write(Data, uint32_t);

};








#endif // FRAM_HPP