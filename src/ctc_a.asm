SECTION code_compiler

PUBLIC _timer_init
_timer_init:
    push    af
    push    bc
    push    hl
    di

    ; set $02 as the MSB of the interrupt vector table base address
    ld  a,$02
    ld  i,a

    ; timer control word
    ld  l,$b7
    ld  c,$e3
    out (c),l

    ; timer constant: T = $9c (156) × P = 256 × (1 / 4MHz) = 10 ms
    ld  l,$9c
    ld  c,$e3
    out (c),l

    ; set LSB of interrupt vector table base address for CTC
    ld  l,$00
    ld  c,$e0
    out (c),l

    ; enable interrupts in Mode 2
    im 2
    ei

    nop
    nop

    pop hl
    pop bc
    pop af
    ret

