#include "audio.h"
#include "cge.h"
#include "compiler.h"
#include "crt.h"
#include "cursor.h"
#include "delay.h"
#include "demo.h"
#include "flipflap.h"
#include "io.h"
#include "lfsr.h"
#include "magiccursor.h"
#include "matrix.h"
#include "mmap.h"
#include "printf.h"
#include "snow.h"
#include "video.h"

void _putchar(char c) {
    video_putchar(c);
}

const uint8_t GLG[28 * 8] = {
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
};

const uint8_t FVB[15 * 8] = {
    1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
    1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0,
    0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1,
    0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0,
    1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0,
};

// Disclaimer: this demo is a bit messy and is not a good programming example.
// Forewarned is forearmed.
int main(void) {
    mmap_set(MMAP_MODE_CEDA_VIDEO);
    demo_init();

    cursor_enable(false);
    video_cls();

    for (;;) {
        if (demo_isEnabled(DEMO_INTRO)) {
            flipflap_init(GLG, 28, 8, 8, 26);
            while (!flipflap_finished()) {
                flipflap_poll();
                crt_waitNextFrame();
            }
            video_enableHorizontalStretch(true);
            video_enableVerticalStretch(true);
            video_locate(18, 15);
            printf("RetrOfficina GLG Programs");
            video_enableHorizontalStretch(false);
            video_enableVerticalStretch(false);
            video_locate(20, 22);
            printf("http://retrofficina.glgprograms.it/");

            crt_waitFrames(250);
        }

        if (demo_isEnabled(DEMO_FVB)) {
            video_cls();
            crt_waitFrames(100);
            flipflap_init(FVB, 15, 8, 2, 40 - 15 / 2);
            while (!flipflap_finished()) {
                flipflap_poll();
                crt_waitNextFrame();
            }

            video_enableHorizontalStretch(true);
            video_enableVerticalStretch(true);
            video_locate(10, 21);
            printf("Firenze Vintage Bit");
            video_locate(12, 36);
            printf("2023");

            crt_waitFrames(250);
        }

        if (demo_isEnabled(DEMO_MATRIX)) {
            video_cls();
            crt_waitFrames(100);
            const uint8_t trails[] = {5, 10, 20, 50};
            for (uint8_t t = 0; t < countof(trails); ++t) {
                matrix_init(trails[t]);
                for (size_t f = 0; f < 120; ++f) {
                    matrix_poll();
                    crt_waitFrames(2);
                }
            }
        }

        if (demo_isEnabled(DEMO_CURSOR)) {
            crt_waitFrames(100);
            magicCursor_run();
            crt_waitFrames(100);
        }

        if (demo_isEnabled(DEMO_CGE)) {
            cge_run();
        }
    }
}
