#include "video.h"

#include "io.h"

#include <stdint.h>

char *const VIDEO_MEMORY = (char *)0xd000;
static uint16_t offset = 0;
static bool hstretch = false;
static bool vstretch = false;

void video_locate(uint8_t row, uint8_t column) {
    offset = (uint16_t)row * 80 + column;
}

void video_enableHorizontalStretch(bool enable) {
    hstretch = enable;
}

void video_enableVerticalStretch(bool enable) {
    vstretch = enable;
}

void video_putchar(char c) {
    // TODO(giomba): this function is not very consistent :sweat:
    if (c == '\n' || c == '\r') {
        offset += 80 - (offset % 80);
        goto end;
    }

    if (hstretch) {
        io_out(0x81, io_in(0x81) | 0x80);
        *(VIDEO_MEMORY + offset) |= 0x08;
        io_out(0x81, io_in(0x81) & ~0x80);
    }

    if (c == '\t') {
        offset += 8 - offset % 8;
        goto end;
    }

    *(VIDEO_MEMORY + offset) = c;

    if (vstretch) {
        *(VIDEO_MEMORY + offset + 80) = c;

        io_out(0x81, io_in(0x81) | 0x80);
        *(VIDEO_MEMORY + offset) |= 0x60;
        *(VIDEO_MEMORY + offset + 80) |= 0x70;
        if (hstretch)
            *(VIDEO_MEMORY + offset + 80) |= 0x08;
        io_out(0x81, io_in(0x81) & ~0x80);
    }

    ++offset;

    if (hstretch)
        ++offset;

end:
    offset = offset % 2000;
}

void video_put(uint8_t x, uint8_t y, char c) {
    if (x >= 80)
        return;
    if (y >= 25)
        return;

    *(VIDEO_MEMORY + x + y * 80) = c;
}
