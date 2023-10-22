SECTION code
PUBLIC _video_cls

_video_cls:
    push    af
    push    bc
    push    de
    push    hl

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

    pop     hl
    pop     de
    pop     bc
    pop     af

    ret
