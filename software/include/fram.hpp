

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
    
    bool init(uint8_t);

    bool read(Data *);

    bool write(Data);

};








#endif // FRAM_HPP