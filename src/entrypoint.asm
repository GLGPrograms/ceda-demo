EXTERN _main

entrypoint:
    ld sp,0xc000

    call _main

    jp ASMPC

