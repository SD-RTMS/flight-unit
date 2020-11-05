#ifndef MEMORY_IF_HPP
#define MEMORY_IF_HPP

#include "fram.hpp"
#include "messages.pb.h"

class memory_if
{
private:
    fram *devices; 
    bool debug;
    unsigned long int *err_cnt;

    uint8_t majority_voter(downlink_proto_SystemMetrics d1, downlink_proto_SystemMetrics d2, downlink_proto_SystemMetrics d3);
    bool ecc_check(downlink_proto_SystemMetrics data);

public:
    memory_if();
    ~memory_if();

    bool init();
    downlink_proto_SystemMetrics read(downlink_proto_SystemMetrics data);
    bool write(downlink_proto_SystemMetrics data);

};


#endif // MEMORY_IF_HPP