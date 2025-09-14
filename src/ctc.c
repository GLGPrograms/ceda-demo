#include "ctc.h"

#include <stddef.h>

static ticks_t ticks = 0;

static timer_user_isr_t user_isr = NULL;

void timer_isr(void) {
    ticks += 1;
    if (user_isr)
        user_isr(ticks);
}

void timer_setISR(timer_user_isr_t isr) {
    user_isr = isr;
}
