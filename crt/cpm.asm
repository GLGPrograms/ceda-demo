; C startup code when running under CP/M
SECTION code_compiler
    org $100

EXTERN _main

PUBLIC __Start

__Start:
    call _main
    ret
