#ifndef CEDA_IO_H
#define CEDA_IO_H

#include <stdint.h>

void io_out(uint8_t address, uint8_t value);

uint8_t io_in(uint8_t address);

#endif // CEDA_IO_H
