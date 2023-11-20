SECTION code
PUBLIC _video_cls

_video_cls:
    push    af
    push    bc
    push    de
    push    hl

    ; clear chars
    ld      hl,$d000
    ld      de,2000
    ld      c,$20
_video_cls_loop:
    ld      (hl),c
    inc     hl
    dec     de
    ld      a,d
    or      e
    jp      nz,_video_cls_loop

    ; enable attr video bank
    in      a,($81)
    or      a,$80
    out     ($81),a

    ; clear attributes
    ld      hl,$d000
    ld      de,2000
    ld      c,$00
_video_attr_cls_loop:
    ld      (hl),c
    inc     hl
    dec     de
    ld      a,d
    or      e
    jp      nz,_video_attr_cls_loop

    ; restore char video bank
    in      a,($81)
    and     a,$7f
    out     ($81),a

    pop     hl
    pop     de
    pop     bc
    pop     af

    ret
