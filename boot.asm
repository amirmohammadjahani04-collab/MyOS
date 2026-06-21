BITS 32
GLOBAL _start
EXTERN kernel_main

SECTION .text

_start:
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang
