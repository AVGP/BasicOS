load:
    push dx                     ; We'll remember how many sectors we wanted
    mov ah, 0x02                ; Read from disk function (BIOS)
    mov al, dh                  ; How many sectors?
    mov ch, 0                   ; Cylinder 0
    mov cl, 2                   ; Sector 2 (after boot sector)
    mov dh, 0                   ; Head 0
    int 0x13                    ; Read from disk (BIOS)
    jc load_error               ; If carry flag is set, we got an error
    pop dx                      ; Let's see what we got..
    cmp al, dh                  ; AL is sectors actually read
                                ; DL is the num of sectors we wanted to read
    jne load_error              ; not read as many as we wanted :/
    ret

load_error:
    mov bx, load_err_msg
    call print
    jmp $

load_err_msg: db "Cannot load from disk", 0
