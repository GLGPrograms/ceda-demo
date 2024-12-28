#include "cge.h"

#include "crt.h"
#include "mmap.h"
#include "printf.h"
#include "snow.h"
#include "video.h"

#include <stdint.h>

#define CGE_SNOW_FRAMES 8

void cge_run(void) {
    char *const VMEM = (char *)0xd000u;

    video_cls();
    video_locate(10, 16);
    printf("to see this part, you need the CGE mod installed");
    crt_waitFrames(4 * CRT_FRAMES_PER_SECOND);
    video_cls();
    crt_waitFrames(2 * CRT_FRAMES_PER_SECOND);

    {
        mmap_set(MMAP_MODE_CEDA_VIDEO);
        extern unsigned char hello_imc[];
        unsigned char *sptr = hello_imc;
        unsigned char *const send = hello_imc + 2000;
        unsigned char *dptr = VMEM;
        while (sptr != send)
            *dptr++ = *sptr++;
    }
    {
        mmap_set(MMAP_MODE_CEDA_ATTR);
        for (int i = 0; i < 2000; ++i) {
            VMEM[i] = 0x80;
        }
        for (int i = 0; i < 80; ++i) {
            VMEM[80 * 20 + i] = 0x00;
        }
    }

    mmap_set(MMAP_MODE_CEDA_VIDEO);
    video_locate(20, 5);
    printf("Custom graphic chars! And we can even mix them with standard "
           "letters \x91");

    crt_waitFrames(5 * CRT_FRAMES_PER_SECOND);
    video_cls();

    // Let's dedicate the left part of the display to the new graphics chars...
    for (uint_least8_t i = 0; i < 2; ++i) {
        enum mmap_mode_t mode =
            (i == 0) ? MMAP_MODE_CEDA_VIDEO : MMAP_MODE_CEDA_ATTR;
        char value = (i == 0) ? 0x00 : 0x80;
        mmap_set(mode);

        for (uint8_t x = 0; x < 36; ++x) {
            char *ptr = VMEM + x;
            for (uint8_t y = 0; y < 25; ++y) {
                *ptr = value;
                ptr += 80;
            }
        }
    }
    // ...and the right part is reserved for the standard characters.
    for (uint_least8_t i = 0; i < 2; ++i) {
        enum mmap_mode_t mode =
            (i == 0) ? MMAP_MODE_CEDA_VIDEO : MMAP_MODE_CEDA_ATTR;
        char value = (i == 0) ? 0x20 : 0x00;
        mmap_set(mode);

        for (uint8_t x = 36; x < 80; ++x) {
            char *ptr = VMEM + x;
            for (uint8_t y = 0; y < 25; ++y) {
                *ptr = value;
                ptr += 80;
            }
        }
    }

    mmap_set(MMAP_MODE_CEDA_VIDEO);

    // Copy Christmas tree image
    extern unsigned char ctree_imc[];
    for (int i = 0; i < 2000; ++i) {
        VMEM[i] = ctree_imc[i];
    }

    // Write wishing words in their place
    video_enableVerticalStretch(true);
    video_enableHorizontalStretch(true);
    video_locate(8, 36);
    printf("Merry Christmas 2024");
    video_locate(12, 36);
    printf("Happy New Year 2025");

    // Marketing :-)
    video_enableVerticalStretch(false);
    video_enableHorizontalStretch(false);
    video_enableUnderline(true);
    video_locate(20, 40);
    printf("retrofficina.glgprograms.it");
    video_enableUnderline(false);

    snow_init();
    for (uint_least16_t i = 0; i < 10 * CRT_FRAMES_PER_SECOND / CGE_SNOW_FRAMES;
         ++i) {
        snow_update();
        crt_waitFrames(CGE_SNOW_FRAMES);
    }

    video_cls();
    crt_waitFrames(2 * CRT_FRAMES_PER_SECOND);

    // Left standard/right extended
    for (uint_least8_t i = 0; i < 2; ++i) {
        char value;
        enum mmap_mode_t mode =
            (i == 0) ? MMAP_MODE_CEDA_VIDEO : MMAP_MODE_CEDA_ATTR;
        mmap_set(mode);

        value = (i == 0) ? ' ' : 0x00;
        for (uint8_t x = 0; x < 40; ++x) {
            char *ptr = VMEM + x + 4 * 80;
            for (uint8_t y = 4; y < 25; ++y) {
                *ptr = value;
                ptr += 80;
            }
        }

        value = (i == 0) ? 0x00 : 0x80;
        for (uint8_t x = 40; x < 80; ++x) {
            char *ptr = VMEM + x + 4 * 80;
            for (uint8_t y = 4; y < 25; ++y) {
                *ptr = value;
                ptr += 80;
            }
        }
    }

    mmap_set(MMAP_MODE_CEDA_VIDEO);
    video_locate(2, 14);
    printf("STANDARD SET");
    video_locate(2, 40 + 14);
    printf("EXTENDED SET");

    for (uint_least16_t i = 0; i < 256; ++i) {
        video_put(12 + i % 16, 4 + i / 16, i);
    }
    for (uint_least16_t i = 0; i < 256; ++i) {
        video_put(40 + 12 + i % 16, 4 + i / 16, i);
    }
    crt_waitFrames(4 * CRT_FRAMES_PER_SECOND);

    video_cls();
    crt_waitFrames(2 * CRT_FRAMES_PER_SECOND);
}