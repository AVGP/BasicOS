[org 0x7c00]
[bits 16]
    mov bp, 0x8000              ; point the base pointer
    mov sp, bp                  ; to a nice location for our stack
    mov bx, bootstring          ; load the message for
    call print                  ; printing..

    mov [BOOT_DRIVE], dl        ; thx, BIOS
    mov dh, 15                  ; Read 15 sectors
    mov bx, KERNEL_OFFSET       ; Destination for load
    call load
    call init_protected
loop:
	jmp loop

bootstring:   db "Basic OS loading...", 0
BOOT_DRIVE:   db 0

KERNEL_OFFSET equ 0x1000

%include "boot/print.asm"
%include "boot/load.asm"
%include "boot/gdt.asm"

times 510 -( $ - $$ ) db 0      ; Fill the sector except for the last 2 byte
dw 0xAA55                       ; which are the magic number for a boot sector
