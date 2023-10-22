#include "video.h"

#include <stdint.h>

char *const VIDEO_MEMORY = (char *)0xd000;
static uint16_t offset = 0;

void video_putchar(char c) {
    if (c == '\n' || c == '\r') {
        offset += 80 - (offset % 80);

    } else if (c == '\t') {
        offset += 8 - offset % 8;
    } else {
        *(VIDEO_MEMORY + offset++) = c;
    }

    offset = offset % 2000;
}

void video_put(uint8_t x, uint8_t y, char c) {
    if (x >= 80)
        return;
    if (y >= 25)
        return;

    *(VIDEO_MEMORY + x + y * 80) = c;
}
