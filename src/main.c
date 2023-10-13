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
