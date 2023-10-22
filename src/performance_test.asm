SECTION code

PUBLIC _performance_test
_performance_test:
    in  a,($A0)

    ld  de,$0100
loop:
    ld  a,($d000)           ; 13

    dec de                  ; 6
    ld  a,d                 ; 4
    or  e                   ; 4
    jp  nz,loop             ; 10

    jp  _performance_test

