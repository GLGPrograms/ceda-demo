    ; $0100     ; .COM entrypoint
    ; $0101     ; .COM entrypoint
    ; $0102     ; .COM entrypoint
    ; $0103     ; .COM exit point
    ; $0104     ; NOP
    ; $0105     ; NOP
    REPT $0106 - ASMPC - $0100
    nop
    ENDR

; IVT - Interrupt Vector Table
; IVT is located at $0100, but first part is actually unused
; because it contains the CP/M .COM entrypoint and exit point
; $0106
PUBLIC ivt
ivt:
    BYTE (z80_a_timer_isr & $ff)
    BYTE (z80_a_timer_isr >> 8)

EXTERN _timer_isr
PUBLIC z80_a_timer_isr
z80_a_timer_isr:
    exx
    ex af,af'
    push ix
    push iy

    call _timer_isr

    pop iy
    pop ix
    ex af,af'
    exx

    ei
    reti

