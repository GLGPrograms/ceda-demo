SECTION code_compiler
    org $1000

EXTERN _main

PUBLIC __Start

__Start:
    ld sp,0xc000

    call _main

    jp ASMPC
