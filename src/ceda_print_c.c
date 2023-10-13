#include "ceda_print.h"

void ceda_print(const char *s) {
    static char *const VIDEO_MEMORY = (char *const)(0xd000);

    char *p = VIDEO_MEMORY;

    while (*s != '\0') {
        *p++ = *s++;
    }
}
