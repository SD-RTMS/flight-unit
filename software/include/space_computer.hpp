#ifndef SPACE_COMPUTER_HPP
#define SPACE_COMPUTER_HPP

#include <Wire.h>
#include "pins.hpp"
#include "data.hpp"

class space_computer
{
private:
    const uint8_t address = 7; // TODO: update
public:

    bool init();
    bool read(Data *, uint8_t);
    
};

#endif // SPACE_COMPUTER_HPP