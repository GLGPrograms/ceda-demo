#include "flipflap.h"

#include "lfsr.h"
#include "video.h"

typedef struct FlipFlapContext {
    const char *image;
    uint8_t width;
    uint8_t height;
    uint8_t row;
    uint8_t column;
    bool finished;
} FlipFlapContext;

static FlipFlapContext ctx;

void flipflap_init(const uint8_t *image, uint8_t width, uint8_t height,
                   uint8_t row, uint8_t column) {
    ctx.image = image;
    ctx.width = width;
    ctx.height = height;
    ctx.row = row;
    ctx.column = column;
    ctx.finished = false;

    Lfsr lfsr;
    lfsr_init(&lfsr, 0xceda);

    for (uint8_t y = 0; y < ctx.height; ++y) {
        for (uint8_t x = 0; x < ctx.width; ++x) {
            if (*(ctx.image + y * ctx.width + x) == 1) {
                *(VIDEO_MEMORY + 80 * (ctx.row + y) + ctx.column + x) =
                    lfsr_next(&lfsr) % 256;
            }
        }
    }
}

void flipflap_poll(void) {
    ctx.finished = true;
    for (uint8_t y = 0; y < ctx.height; ++y) {
        for (uint8_t x = 0; x < ctx.width; ++x) {
            if (*(ctx.image + y * ctx.width + x) == 1) {
                char *p = VIDEO_MEMORY + 80 * (ctx.row + y) + ctx.column + x;
                if (*p != 0x86) {
                    *p += 1;
                    ctx.finished = false;
                }
            }
        }
    }
}

bool flipflap_finished(void) {
    return ctx.finished;
}