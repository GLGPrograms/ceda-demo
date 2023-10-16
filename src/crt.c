#include "crt.h"

#include <stdint.h>

void crt_waitNextFrame(void) {
    void (*frame_sync_detection_routine)(void) = (void *)0xc75b;
    __asm__("push af");
    frame_sync_detection_routine();
    __asm__("pop af");
}