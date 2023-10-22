#ifndef CEDA_CURSOR_H
#define CEDA_CURSOR_H

#include <stdbool.h>
#include <stdint.h>

void cursor_setRaw(uint16_t address);

void cursor_setXY(uint8_t x, uint8_t y);

void cursor_setStartRaster(uint8_t start);

void cursor_setEndRaster(uint8_t end);

void cursor_enable(bool enable);

#endif
