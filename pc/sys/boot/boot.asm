; boot.asm (NASM)
[bits 32]
extern kernel_main

global start
start:
    call kernel_main
    jmp $
