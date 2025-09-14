; C startup code for serial loader (BIOS-only)
SECTION code_compiler
    org $100

EXTERN _main

PUBLIC __Start

__Start:
    ld sp,0xb000
    call _main
    ; main must never return
    ; and nothing must be put here,
    ; because this memory are is shared with the IVT
INCLUDE "timer_crt.asm"

