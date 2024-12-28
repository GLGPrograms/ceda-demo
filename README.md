# ceda-demo

Demo for the Sanco 800x.

The purpose of this demo is mainly to thinker with the hardware of the mentioned computer, since we are reverse-engineering it, and even writing an emulator.

It also demonstrates some hardware capabilities of the machine, exploits some custom mods, and its build system can be used as a template for new applications in C and assembly.

This repository is part of the [CEDA project](https://github.com/GLGPrograms/ceda-home) by [Retrofficina GLG Programs](https://retrofficina.glgprograms.it/).

## C/ASM calling conventions
Because the folks at z88dk were not able to put this plain and simple table
in their messy documentation :smile:

### Prologue
```
    push    ix
    ld      ix,$0000
    add     ix,sp
```

### Parameters stack
```
    uint8_t
        ix+$04

    uint8_t, uint8_t
        ix+$04, ix+$05
```

### Access call parameters
```
    ld      a,(ix+$04)
    ld      a,(ix+$05)
```

### Return value
```
    uint32_t    de (msb), hl (lsb)
    uint16_t    hl
    uint8_t     l
    void*       hl
```

### Epilogue
```
    pop     ix
    ret
```

