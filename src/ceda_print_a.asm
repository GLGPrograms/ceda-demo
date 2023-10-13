SECTION code
PUBLIC _ceda_cls

_ceda_cls:
    push    af
    push    bc
    push    de
    push    hl

    ld      hl,$d000
    ld      de,2000
    ld      c,$20
_ceda_cls_loop:
    ld      (hl),c
    inc     hl
    dec     de
    ld      a,d
    or      e
    jp      nz,_ceda_cls_loop

    pop     hl
    pop     de
    pop     bc
    pop     af

    ret
