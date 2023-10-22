#include "crt.h"

void crt_waitNextFrame(void) {
    void (*frame_sync_detection_routine)(void) = (void *)0xc75b;
    __asm__("push af");
    frame_sync_detection_routine();
    __asm__("pop af");
}

void crt_waitFrames(uint16_t n) {
    for (uint16_t i = 0; i < n; ++i)
        crt_waitNextFrame();
}
