#include "lfsr.h"

void lfsr_init(Lfsr *ctx, uint16_t init) {
    ctx->lfsr = init;
    ctx->bit = 0;
}

uint16_t lfsr_next(Lfsr *ctx) {
    ctx->bit = ((ctx->lfsr >> 0) ^ (ctx->lfsr >> 2) ^ (ctx->lfsr >> 3) ^
                (ctx->lfsr >> 5)) &
               1U;
    ctx->lfsr = (ctx->lfsr >> 1) | (ctx->bit << 15);
    return ctx->lfsr;
}
