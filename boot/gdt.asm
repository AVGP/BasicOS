gdt:                
gdt_null:           ; Required null selector
    dd 0            ; Selectors are 2 * 8 byte long
    dd 0            ; so we use double words here
gdt_cs:
    dw 0xffff       ; Limit
    dw 0            ; Base (lower word)
    db 0            ; Base (first part of the higher word)
    db 10011010b    ; present? privilege (2bit) descriptor_type 
                    ; code? conforming? readable? accessed?
    db 11001111b    ; granularity 32bit? 64bit? AVL + 4bit limit
    db 0            ; Base (second part of the higher word)
gdt_ds:
    dw 0xffff       ; Limit
    dw 0            ; Base (lower word)
    db 0            ; Base (first part of the higher word)
    db 10010010b    ; present? privilege (2bit) descriptor_type
                    ; code? conforming? readable? accessed?
    db 11001111b    ; granularity 32bit? 64bit? AVL + 4bit limit
    db 0            ; Base (second part of the higher word)
gdt_end:            ; Marker for easier calculations

gdt_desc:
    dw gdt_end - gdt - 1
    dd gdt

CODE_SEG equ gdt_cs - gdt
DATA_SEG equ gdt_ds - gdt

[bits 16]

init_protected:
    cli
    xor ax, ax
    mov ds, ax
    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:start_protected

[bits 32]

start_protected:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x90000
    mov esp, ebp
;    sti
    
    call KERNEL_OFFSET 
    jmp $
