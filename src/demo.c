#include "demo.h"

#include "string.h"

static bool demo_enable[DEMO_COUNT] = {false};

void demo_init(void) {
    _memset(demo_enable, true, sizeof(demo_enable));
#if 0
    demo_enable[DEMO_INTRO] = false;
    demo_enable[DEMO_FVB] = false;
    demo_enable[DEMO_MATRIX] = false;
    demo_enable[DEMO_CURSOR] = false;
    demo_enable[DEMO_CGE] = true;
    demo_enable[DEMO_AUDIO] = true;
#endif
}

void demo_setEnabled(enum demo_part_t part, bool enable) {
    demo_enable[part] = enable;
}

bool demo_isEnabled(enum demo_part_t part) {
    return demo_enable[part];
}
