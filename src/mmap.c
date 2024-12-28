#include "mmap.h"

#include "io.h"

#define MMAP_VALID_BITS 0x81
#define MMAP_PORT_ADDR  0x81

void mmap_set(enum mmap_mode_t mode) {
    io_out(MMAP_PORT_ADDR, (io_in(MMAP_PORT_ADDR) & ~MMAP_VALID_BITS) |
                               (mode & MMAP_VALID_BITS));
}

enum mmap_mode_t mmap_get(void) {
    return io_in(MMAP_PORT_ADDR);
}
