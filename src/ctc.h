#ifndef CEDA_TIMER_H
#define CEDA_TIMER_H

#define TIMER_TICKS_PER_SEC (100)

#include <stdint.h>

typedef int16_t ticks_t;

typedef void (*timer_user_isr_t)(ticks_t);

void timer_init(void);

void timer_setISR(timer_user_isr_t isr);

void timer_cleanup(void);

#endif
