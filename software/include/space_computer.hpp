#ifndef SPACE_COMPUTER_HPP
#define SPACE_COMPUTER_HPP

#include <Wire.h>
#include "pins.hpp"
#include "messages.pb.h"

class space_computer
{
private:
    const uint8_t address = 7; // TODO: update
public:

    bool init();
    downlink_proto_SystemMetrics read(downlink_proto_SystemMetrics data, uint8_t);
};

#endif // SPACE_COMPUTER_HPP