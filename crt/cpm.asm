; C startup code when running under CP/M
SECTION code_compiler
    org $100

EXTERN _main

PUBLIC __Start

; Note: be careful if you move things around here
; because this code is embedded in ad unused portion
; of the Interrupt Vector Table
__Start:
    call _main
    ret

INCLUDE "timer_crt.asm"

