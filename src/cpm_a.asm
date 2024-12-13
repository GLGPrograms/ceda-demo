SECTION code

cpm_syscall = $0005

PUBLIC _cpm_printChar
_cpm_printChar:
    push    ix
    ld      ix,$0000
    add     ix,sp

    push    de

    ld      e,(ix+$04)
    ld      c,$02
    call    cpm_syscall

    pop     de

    pop ix
    ret

