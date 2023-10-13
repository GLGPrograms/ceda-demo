#include "ceda_print.h"
#include "io.h"

int globalvar = 0x7777;

int main(void) {
    ceda_print("Hello world!");
    ceda_cls();

    io_out(0x81, 0x80);
    ceda_print("ABCD");

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
