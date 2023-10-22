#ifndef CEDA_FLIPFLAP_H
#define CEDA_FLIPFLAH_H

#include <stdbool.h>
#include <stdint.h>

void flipflap_init(const uint8_t *image, uint8_t width, uint8_t height,
                   uint8_t row, uint8_t column);
void flipflap_poll(void);
bool flipflap_finished(void);

#endif
