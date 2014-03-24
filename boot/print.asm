print:
    mov ah, 0xE                 ; Teletype output
    mov al, [bx]                ; load the character at bx
    cmp al, 0                   ; is it the terminator (Ascii 0)?
    jz print_done               ; If it is, we're done
    int 0x10                    ; Print to screen
    inc bx                      ; Next byte of the string
    jmp print                   ; rinse, repeat
print_done:
    ret
