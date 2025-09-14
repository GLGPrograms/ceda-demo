#ifndef CEDA_DEMO_DEMO_H
#define CEDA_DEMO_DEMO_H

#include <stdbool.h>

enum demo_part_t {
    DEMO_INTRO,
    DEMO_FVB,
    DEMO_MATRIX,
    DEMO_CURSOR,
    DEMO_CGE,
    DEMO_AUDIO,

    DEMO_COUNT,
};

void demo_init(void);
void demo_setEnabled(enum demo_part_t part, bool enable);
bool demo_isEnabled(enum demo_part_t part);

#endif