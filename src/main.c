#include "ceda_print.h"
#include "crt.h"
#include "cursor.h"
#include "delay.h"
#include "io.h"

static void wait(void) {
    (void)io_in(0xA0);

    for (;;) {
        const uint8_t port_c = io_in(0x82);
        if (port_c & 0x2)
            break;
    }
}

int main(void) {
    ceda_print("Hello world!");

    ceda_cls();

#if 0
    for (int i = 0; i < 80; ++i) {
        cursor_setXY(i, 0);

        // TODO(giomba): add vsync?
        delay_loop(US_TO_LOOPS(10000ULL));
    }
#endif

    int counter = 0;
    __asm__("di");

#if 0
    for (;;) {
        for (int i = 0; i < 50; ++i)
            crt_waitNextFrame();

        // wait();
        counter++;

        int scratch = counter;
        uint8_t digits[4];
        digits[3] = scratch % 10;
        scratch /= 10;
        digits[2] = scratch % 10;
        scratch /= 10;
        digits[1] = scratch % 10;
        scratch /= 10;
        digits[0] = scratch % 10;

        for (int i = 0; i < 4; ++i) {
            digits[i] += '0';
            *((char *)(0xd000 + i)) = digits[i];
        }
    }
#endif

    cursor_setXY(39, 10);

    for (;;) {
        for (int i = 0; i < 16; ++i) {
            cursor_setStartRaster(0);
            cursor_setEndRaster(i);
            for (int j = 0; j < 8; ++j)
                crt_waitNextFrame();
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
