SECTION code

PUBLIC _delay_loop
_delay_loop:
    ; function prologue: use IX to index parameters passed on the stack
    push    ix          ; 15
    ld      ix,$0000    ; 14
    add     ix,sp       ; 15

    ; save scratch registers
    push    af          ; 11
    push    de          ; 11

    ; load loop counter into DE
    ld      d,(ix+$05)  ; 19
    ld      e,(ix+$04)  ; 19

    ; delay loop (24 × n)
_delay_loop_loop:
    dec     de          ; 6
    ld      a,d         ; 4
    or      e           ; 4
    jp      nz,_delay_loop_loop ; 10

    ; restore scratch registers
    pop     de          ; 10
    pop     af          ; 10

    ; restore IX
    pop     ix          ; 14

    ret



