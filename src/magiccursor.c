#include "magiccursor.h"

#include "crt.h"
#include "cursor.h"
#include "delay.h"
#include "io.h"
#include "printf.h"
#include "video.h"

#include <stdbool.h>

void magicCursor_run(void) {
    cursor_enable(false);
    video_cls();

    // maximum raster raster
    io_out(0xA0, 9);
    io_out(0xA1, 0xf);

    video_enableVerticalStretch(false);
    video_enableHorizontalStretch(false);
    video_locate(12, 35);
    printf("THE CURSOR");
    crt_waitFrames(50);

    cursor_setXY(45, 12);
    cursor_setStartRaster(13);
    cursor_setEndRaster(13);
    cursor_blink(CURSOR_BLINK_FAST);
    cursor_enable(true);
    crt_waitFrames(100);

    cursor_blink(CURSOR_BLINK_SLOW);
    crt_waitFrames(100);

    cursor_blink(CURSOR_BLINK_NONE);
    crt_waitFrames(100);

    for (uint8_t x = 45; x >= 40; --x) {
        cursor_setXY(x, 12);
        crt_waitFrames(20);
    }
    cursor_setXY(40, 13);
    crt_waitFrames(100);

    for (int8_t i = 13; i >= 0; --i) {
        cursor_setStartRaster(i);
        cursor_setEndRaster(i);
        crt_waitFrames(4);
    }

    for (uint8_t j = 0; j < 3; ++j) {
        for (int8_t i = 1; i < 16; ++i) {
            cursor_setStartRaster(i);
            cursor_setEndRaster(i);
            crt_waitFrames(4);
        }
        for (int8_t i = 14; i >= 0; --i) {
            cursor_setStartRaster(i);
            cursor_setEndRaster(i);
            crt_waitFrames(4);
        }
    }

    for (int8_t i = 1; i < 64; ++i) {
        cursor_setXY(40, 13 + i / 16);
        cursor_setStartRaster(i % 16);
        cursor_setEndRaster(i % 16);
        crt_waitFrames(4);
    }

    cursor_setXY(40, 16);
    for (uint8_t j = 0; j < 3; ++j) {
        for (int8_t i = 14; i >= 0; --i) {
            cursor_setStartRaster(i);
            crt_waitFrames(4);
        }
        for (int8_t i = 14; i >= 0; --i) {
            cursor_setEndRaster(i);
            crt_waitFrames(4);
        }
        for (int8_t i = 1; i < 16; ++i) {
            cursor_setEndRaster(i);
            crt_waitFrames(4);
        }
        for (int8_t i = 1; i < 16; ++i) {
            cursor_setStartRaster(i);
            crt_waitFrames(4);
        }
    }

    cursor_enable(false);
}