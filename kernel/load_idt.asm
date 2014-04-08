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

[global irq0]
[global irq1]
[global irq2]
[global irq3]
[global irq4]
[global irq5]
[global irq6]
[global irq7]
[global irq8]
[global irq9]
[global irq10]
[global irq11]
[global irq12]
[global irq13]
[global irq14]
[global irq15]


[extern idtp]
[extern exception_handler]
[extern irq_handler]

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

irq_common_stub:
   pusha

   mov ax, ds
   push eax

   mov ax, 0x10
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call irq_handler

   pop ebx
   mov ds, bx
   mov es, bx
   mov fs, bx
   mov gs, bx

   popa
   add esp, 8
   sti
   iret
