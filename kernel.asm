BITS 32

section .multiboot
    dd 0x1BADB002
    dd 0
    dd -(0x1BADB002)

section .text
global _start

_start:
    mov esi, msg

print:
    lodsb
    or al, al
    jz hang

    mov ah, 0x0E
    int 0x10
    jmp print

hang:
    jmp hang

msg db "My OS Kernel Booted!", 0
