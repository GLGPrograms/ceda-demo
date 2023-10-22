#include "matrix.h"
#include "compiler.h"
#include "crt.h"
#include "lfsr.h"
#include "video.h"

#include <stddef.h>

typedef struct MatrixLetter {
    int8_t row;
    int8_t trail_row;
    uint8_t column;
} MatrixLetter;

typedef struct MatrixContext {
    Lfsr lfsr;
    uint8_t trail;
    MatrixLetter letters[80];
} MatrixContext;

static MatrixContext mctx;

static void matrixLetter_init(MatrixLetter *ctx) {
    ctx->column = lfsr_next(&mctx.lfsr) % 80;
    ctx->row = lfsr_next(&mctx.lfsr) % 50 - 50;
    ctx->trail_row = ctx->row - (lfsr_next(&mctx.lfsr) % mctx.trail + 3);
}

static void matrixLetter_poll(MatrixLetter *ctx) {
    ctx->row++;
    ctx->trail_row++;
    if (ctx->row < 0)
        return;

    const uint8_t c = lfsr_next(&mctx.lfsr) % 256;
    video_put(ctx->column, ctx->row, c);

    if (ctx->trail_row < 0)
        return;
    video_put(ctx->column, ctx->trail_row, ' ');
}

void matrix_init(uint8_t trail) {
    lfsr_init(&mctx.lfsr, 1);
    mctx.trail = trail;

    // using the same LFSR for different letters makes the randomness
    // not reproducible in case we decide to refactor the number of letters,
    // but that's not an issue we care about at the moment
    for (size_t i = 0; i < countof(mctx.letters); ++i) {
        matrixLetter_init(&mctx.letters[i]);
    }
}

void matrix_poll(void) {
    for (size_t i = 0; i < countof(mctx.letters); ++i) {
        matrixLetter_poll(&mctx.letters[i]);
    }
}
