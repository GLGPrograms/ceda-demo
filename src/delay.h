#ifndef CEDA_DELAY_H
#define CEDA_DELAY_H

/*
    Assuming a Z80 CPU running at 4MHz, the chosen assembly loop
    permits busy loops withing the following specs:

    min: 37 us
    max: 393253 ms
    precision: 6 us

    For example, to wait for 50 us use the following.
    This will actually busy wait for 47 us due to precision losses.
        delay_us(US_TO_LOOPS(50));
*/

#include <stdint.h>

#define CPU_FREQ 4000000UL // 4 MHz

#define US_TO_LOOPS(t) ((((t)*CPU_FREQ / 1000000UL) - 148) / 24)

void delay_loop(uint16_t loops);

#endif // CEDA_DELAY_H
