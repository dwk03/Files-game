; boot.asm - minimal BIOS bootloader
; assembles to a single 512-byte boot sector (MBR boot sector)
; usage: nasm -f bin boot.asm -o boot.bin

org 0x7C00           ; BIOS loads boot sector here

start:
    cli               ; disable interrupts while we set up
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00    ; simple stack

    sti               ; enable interrupts

    ; Print message using BIOS teletype (INT 10h AH=0Eh)
    mov si, message
.print_char:
    lodsb             ; AL = [SI], SI++
    cmp al, 0
    je .wait_key
    mov ah, 0x0E
    mov bh, 0x00
    mov bl, 0x07      ; page 0, attribute (ignored in teletype)
    int 0x10
    jmp .print_char

.wait_key:
    ; Wait for any key (INT 16h AH=00)
    xor ah, ah
    int 0x16

    ; Reboot via BIOS bootstrap (INT 19h)
    int 0x19

    ; If INT 19h doesn't return, loop here
.halt_loop:
    hlt
    jmp .halt_loop

message db 'Hello from USB bootloader! Press any key to reboot...', 0

; Pad to 510 bytes, then boot signature 0x55AA
times 510 - ($ - $$) db 0
dw 0xAA55
