#ifndef CEDA_PRINT_H
#define CEDA_PRINT_H

#include <stdint.h>

void video_cls(void);
void video_put(uint8_t x, uint8_t y, char c);
void video_putchar(char c);

#endif // CEDA_PRINT_H
