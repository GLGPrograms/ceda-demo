#include "snow.h"

#include "compiler.h"
#include "lfsr.h"
#include "video.h"

#include <stdbool.h>
#include <stdint.h>

// TODO(giomba): this module contains some limitations,
// because I did it in a rush during a frenzy coding marathon
// during Christmas leave.
// Not the best, but it works.
// Things that should be done:
//  - properly handle snow falling in a subset of the display (eg. window)
//  - move snow flakes one pixel at a time (after all, we have CGE, don't we?)

#define SNOW_FLAKE_BIRTH   8000 // snowflake birth probability
#define SNOW_FLAKE_MAX_COL 32   // only work on the left part of the display

#define SNOW_FLAKES_MAX 10
typedef struct flake_t {
    bool active;
    uint_least8_t x;
    uint_least8_t y;
    char prev;
} flake_t;

static struct {
    flake_t flakes[SNOW_FLAKES_MAX];
    Lfsr rand;
} snow;

void snow_init(void) {
    for (uint_least8_t i = 0; i < countof(snow.flakes); ++i) {
        snow.flakes[i].active = false;
    }
    lfsr_init(&snow.rand, 0xceda);
}

void snow_update(void) {
    for (uint_least8_t i = 0; i < countof(snow.flakes); ++i) {
        // if flake not active, try to give birth to it
        if (!snow.flakes[i].active) {
            const uint16_t birth = lfsr_next(&snow.rand);
            if (birth < SNOW_FLAKE_BIRTH) {
                snow.flakes[i].x = birth % SNOW_FLAKE_MAX_COL;
                snow.flakes[i].y = 0;
                snow.flakes[i].prev = 0;
                snow.flakes[i].active = true;
            }
        }
    }

    // restore previous char
    for (uint_least8_t i = 0; i < countof(snow.flakes); ++i) {
        if (snow.flakes[i].active)
            video_put(snow.flakes[i].x, snow.flakes[i].y, snow.flakes[i].prev);
    }

    // move snowflakes
    for (uint_least8_t i = 0; i < countof(snow.flakes); ++i) {
        if (snow.flakes[i].active) {
            snow.flakes[i].y++;
            snow.flakes[i].x += (lfsr_next(&snow.rand) / (65536UL / 5) - 2);
            if (snow.flakes[i].x >= SNOW_FLAKE_MAX_COL) {
                snow.flakes[i].x = SNOW_FLAKE_MAX_COL - 1;
            }
            uint8_t x = snow.flakes[i].x;
            uint8_t y = snow.flakes[i].y;
            char c = video_get(x, y);
            snow.flakes[i].prev = c;

            if (snow.flakes[i].y == 25) {
                snow.flakes[i].active = false;
            }
        }
    }

    // update flakes on the display
    for (uint_least8_t i = 0; i < countof(snow.flakes); ++i) {
        if (snow.flakes[i].active) {
            video_put(snow.flakes[i].x, snow.flakes[i].y,
                      snow.flakes[i].prev | 0x01);
        }
    }
}

void snow_cleanup(void) {}