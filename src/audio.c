#include "audio.h"

#include <stddef.h>
#include <stdint.h>

#include "compiler.h"
#include "ctc.h"
#include "io.h"
#include "printf.h"

#define SN76489_IOADDR (0x00)

static unsigned char *vgm_data = NULL; // all the VGM data in the file
static uint8_t *vgm_music = NULL;      // just the music
static bool end_of_music = false;
static uint8_t unknown_cmd = 0x50;

static uint32_t deserialize_u32(uint8_t *ptr) {
    return *((uint32_t *)ptr); // already using little endian
}

static void audio_playerISR(ticks_t n) {
    (void)n;

    static uint16_t demo_wait_samples = 0;
    if (demo_wait_samples) {
        --demo_wait_samples;
        return;
    }

    if (end_of_music)
        return;

    // parse music data
    while (!demo_wait_samples) {
        uint8_t cmd = *vgm_music++;
        switch (cmd) {
        case 0x50: // write value
        {
            uint8_t value = *vgm_music++;
            io_out(SN76489_IOADDR, value);
            break;
        }

        case 0x61: // wait
        {
            uint16_t vgm_samples = *((uint16_t *)vgm_music);
            vgm_music += 2;
            demo_wait_samples = vgm_samples / 147;
            break;
        }

        case 0x62: // wait 1/60 s
        {
            demo_wait_samples = 5;
            break;
        }

        case 0x63: // wait 1/50 s
        {
            demo_wait_samples = 6;
            break;
        }

        case 0x66: // end of sound data
        {
            end_of_music = true;
            break;
        }

        default:
            unknown_cmd = cmd;
            break;
        }
    }
}

void audio_init(void) {
    extern unsigned char rudolph_vgm[];
    vgm_data = rudolph_vgm;

    uint32_t version = deserialize_u32(&vgm_data[0x08]);
    uint32_t clock = deserialize_u32(&vgm_data[0x0C]);
    uint32_t offset = deserialize_u32(&vgm_data[0x34]);
    vgm_music = &vgm_data[offset + 0x34];

#if 0
    printf("version = %lx, clock = %lu, offset = %lx\n", version, clock,
           offset);
#endif

    timer_init();
    timer_setISR(audio_playerISR);
    end_of_music = false;
}

void audio_cleanup(void) {
    timer_cleanup();

    // set SN76489 attenuators to maximum value (silence!)
    static const uint8_t cmds[] = {0x9f, 0xbf, 0xdf, 0xff};
    for (int_fast8_t i = 0; i < countof(cmds); ++i)
        io_out(SN76489_IOADDR, cmds[i]);

#if 0
        // If the music does not sound very good, probably we are missing some unimplemented commands.
        // This snippet here prints the last unknown command encountered during song playback.
    if (unknown_cmd != 0x50)
        printf("unknown VGM cmd = %x\n", (int)unknown_cmd);
#endif
}

bool audio_run(void) {
    return !end_of_music;
}
