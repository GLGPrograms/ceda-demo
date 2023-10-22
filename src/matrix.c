#include "matrix.h"
#include "compiler.h"
#include "crt.h"
#include "lfsr.h"
#include "video.h"

#include <stddef.h>

#define MATRIX_LETTER_TRAIL 4

typedef struct MatrixLetter {
    Lfsr *lfsr;
    int8_t row;
    uint8_t column;
} MatrixLetter;

typedef struct MatrixContext {
    Lfsr lfsr;
    MatrixLetter letters[80];
} MatrixContext;

static MatrixContext ctx;

static void matrixLetter_init(MatrixLetter *ctx, Lfsr *lfsr) {
    ctx->lfsr = lfsr;
    ctx->column = lfsr_next(ctx->lfsr) % 80;
    ctx->row = lfsr_next(ctx->lfsr) % 50 - 50;
}

static void matrixLetter_poll(MatrixLetter *ctx) {
    ctx->row++;
    if (ctx->row < 0)
        return;

    const uint8_t c = lfsr_next(ctx->lfsr) % 256;
    video_put(ctx->column, ctx->row, c);

    if (ctx->row < MATRIX_LETTER_TRAIL)
        return;
    video_put(ctx->column, ctx->row - MATRIX_LETTER_TRAIL, ' ');
}

void matrix_init(void) {
    lfsr_init(&ctx.lfsr, 1);

    // using the same LFSR for different letters makes the randomness
    // not reproducible in case we decide to refactor the number of letters,
    // but that's not an issue we care about at the moment
    for (size_t i = 0; i < countof(ctx.letters); ++i) {
        matrixLetter_init(&ctx.letters[i], &ctx.lfsr);
    }
}

void matrix_poll(void) {
    for (size_t i = 0; i < countof(ctx.letters); ++i) {
        matrixLetter_poll(&ctx.letters[i]);
    }
}