#ifndef MEMORY_IF_HPP
#define MEMORY_IF_HPP

#include "fram.hpp"

class memory_if
{
private:
    fram *devices; 
    bool debug;
    unsigned long int *err_cnt;

    uint8_t majority_voter(Data, Data, Data);
    bool ecc_check(Data);

public:
    memory_if();
    ~memory_if();

    bool init();
    bool read(Data *);
    bool write(Data);

};


#endif // MEMORY_IF_HPP