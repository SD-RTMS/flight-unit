

#ifndef FRAM_HPP
#define FRAM_HPP

#include "pins.hpp"
#include "data.hpp"
#include <inttypes.h>

class fram
{
private:
    uint8_t cs;

    bool write_byte(uint8_t);

    uint8_t read_byte();

public:
    
    /**
     * @brief initializes the fram module
     * 
     * @return true 
     * @return false 
     */
    bool init(uint8_t);

    /**
     * @brief reads the data packet from the fram module
     * 
     * @return true 
     * @return false 
     */
    bool read(Data *);

    /**
     * @brief writes the packet to the fram module
     * 
     * @return true 
     * @return false 
     */
    bool write(Data);

};








#endif // FRAM_HPP