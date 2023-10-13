SECTION code
PUBLIC _io_out

_io_out:
    push    ix
    ld      ix,$0000
    add     ix,sp

    push bc

    ld      c,(ix+$04)
    ld      b,(ix+$05)
    out     (c),b

    pop     bc

    pop ix
    ret
