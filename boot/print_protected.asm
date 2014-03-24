[bits 32]
    VIDEO_BASE equ 0xB8000  ; Base of video memory chunk
    COLOR_FMT equ 0x0F      ; White on Black
print_protected:
    pusha
    mov edx, VIDEO_BASE
print_prot_loop:
    mov al, [ebx]           ; Char comes from addr in EBX
    mov ah, COLOR_FMT       ; Use the white on black format
    cmp al, 0
    je print_prot_done
    mov [edx], ax           ; Copy into video memory
    add edx, 2              ; Progress one cell in video mem
    add ebx, 1              ; Progress one char in string
    jmp print_prot_loop
print_prot_done:
    popa
    ret
