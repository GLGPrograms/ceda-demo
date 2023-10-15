#include "ceda_print.h"
#include "cursor.h"
#include "delay.h"
#include "io.h"

int main(void) {
    ceda_print("Hello world!");

    // ceda_cls();

    for (;;) {
        for (int i = 0; i < 80; ++i) {
            cursor_setXY(i, 0);

            // TODO(giomba): add vsync?
            delay_loop(US_TO_LOOPS(200000ULL));
        }
    }

    cursor_setStartRaster(5);
    cursor_setEndRaster(10);

    for (;;) {
        for (int i = 0; i < (16 - 1); ++i) {
            cursor_setStartRaster(i);
            cursor_setEndRaster(i + 1);
            delay_loop(US_TO_LOOPS(200000UL));
        }
    }

    return 0;
}

uint8_t ret_u8(void) {
    return 0x01;
}

uint16_t ret_u16(void) {
    return 0x0123;
}

uint32_t ret_u32(void) {
    return 0x01234567;
}

void *ret_ptr(void) {
    return (void *)0x1234;
}
