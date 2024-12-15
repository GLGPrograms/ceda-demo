#include "cursor.h"

#include "io.h"

static uint8_t r10 = 0;

void cursor_setRaw(uint16_t address) {
    io_out(0xA0, 14);
    io_out(0xA1, (address >> 8) & 0xff);
    io_out(0xA0, 15);
    io_out(0xA1, address & 0xff);
}

void cursor_setXY(uint8_t x, uint8_t y) {
    cursor_setRaw((uint16_t)y * 80 + x);
}

void cursor_setStartRaster(uint8_t start) {
    start &= 0x1f;
    r10 &= ~0x1f;
    r10 |= start;
    io_out(0xA0, 10);
    io_out(0xA1, r10);
}

void cursor_setEndRaster(uint8_t end) {
    end &= 0x1f;
    io_out(0xA0, 11);
    io_out(0xA1, end);
}

void cursor_enable(bool enable) {
    if (enable) {
        cursor_setStartRaster(0xd);
        cursor_setEndRaster(0xd);
    } else {
        cursor_setStartRaster(0xd);
        cursor_setEndRaster(0x0);
    }
}

void cursor_blink(enum cursor_blink_t blink) {
    blink &= 0x60;
    r10 &= ~0x60;
    r10 |= blink;
    io_out(0xA0, 10);
    io_out(0xA1, r10);
}
