[global load_idt]
[global isr0]
[global isr1]
[global isr2]
[global isr3]
[global isr4]
[global isr5]
[global isr6]
[global isr7]
[global isr8]
[global isr9]
[global isr10]
[global isr11]
[global isr12]
[global isr13]
[global isr14]
[global isr15]
[global isr16]
[global isr17]
[global isr18]
[global isr19]
[global isr20]
[global isr21]
[global isr22]
[global isr23]
[global isr24]
[global isr25]
[global isr26]
[global isr27]
[global isr28]
[global isr29]
[global isr30]
[global isr31]
[global isr32]


[extern idtp]
[extern exception_handler]

load_idt:
    lidt [idtp]
    ret

%include "kernel/isrs.asm"

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov eax, esp
    push eax

    mov eax, exception_handler
    call eax

    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
