    REPT $0200 - ASMPC - $0100
    nop
    ENDR

; IVT - Interrupt Vector Table
PUBLIC ivt
ivt:
    REPT $0006
    nop
    ENDR
EXTERN z80_a_timer_isr
    BYTE (z80_a_timer_isr & $ff)
    BYTE (z80_a_timer_isr >> 8)

EXTERN _timer_isr
PUBLIC z80_a_timer_isr
z80_a_timer_isr:
    ; TODO(giomba): preserve registers
    exx
    ex af,af'
    call _timer_isr
    ex af,af'
    exx
    ei
    reti

