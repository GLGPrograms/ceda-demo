#ifndef LFSR_H
#define LFSR_H

#include <stdint.h>

typedef struct Lfsr {
    uint16_t lfsr;
    uint16_t bit;
} Lfsr;

void lfsr_init(Lfsr *ctx, uint16_t init);
uint16_t lfsr_next(Lfsr *ctx);

#endif // LFSR_H
