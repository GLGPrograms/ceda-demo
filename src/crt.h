#ifndef CEDA_CRT_H
#define CEDA_CRT_H

#include <stdbool.h>
#include <stdint.h>

#define CRT_FRAMES_PER_SECOND 50

void crt_waitNextFrame(void);
void crt_waitFrames(uint16_t n);

#endif // CEDA_CRT_H
