;  0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

;  1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

;  2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

;  3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

;  4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

;  5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

;  6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub

;  7: Coprocessor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

;  8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8
    jmp isr_common_stub

;  9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push byte 10
    jmp isr_common_stub

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push byte 11
    jmp isr_common_stub

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push byte 12
    jmp isr_common_stub

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push byte 13
    jmp isr_common_stub

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push byte 14
    jmp isr_common_stub

; 15: Reserved Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

; 19: Reserved
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

; 20: Reserved
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

; 21: Reserved
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

; 22: Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

; 23: Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

; 24: Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

; 25: Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

; 26: Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

; 27: Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

; 28: Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

; 29: Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

; 30: Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub

; 31: Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

;
; IRQ trampolines
;

; 32: IRQ0
irq0:
    cli
    push byte 0
    push byte 0
    jmp irq_common_stub

; 33: IRQ1
irq1:
    cli
    push byte 0
    push byte 1
    jmp irq_common_stub

; 34: IRQ2
irq2:
    cli
    push byte 0
    push byte 2
    jmp irq_common_stub

; 35: IRQ3
irq3:
    cli
    push byte 0
    push byte 3
    jmp irq_common_stub

; 36: IRQ4
irq4:
    cli
    push byte 0
    push byte 4
    jmp irq_common_stub

; 37: IRQ5
irq5:
    cli
    push byte 0
    push byte 5
    jmp irq_common_stub

; 38: IRQ6
irq6:
    cli
    push byte 0
    push byte 6
    jmp irq_common_stub

; 39: IRQ7
irq7:
    cli
    push byte 0
    push byte 7
    jmp irq_common_stub

; 40: IRQ8
irq8:
    cli
    push byte 0
    push byte 8
    jmp irq_common_stub

; 41: IRQ9
irq9:
    cli
    push byte 0
    push byte 9
    jmp irq_common_stub

; 42: IRQ10
irq10:
    cli
    push byte 0
    push byte 10
    jmp irq_common_stub

; 43: IRQ11
irq11:
    cli
    push byte 0
    push byte 11
    jmp irq_common_stub

; 44: IRQ12
irq12:
    cli
    push byte 0
    push byte 12
    jmp irq_common_stub

; 45: IRQ13
irq13:
    cli
    push byte 0
    push byte 13
    jmp irq_common_stub

; 46: IRQ14
irq14:
    cli
    push byte 0
    push byte 14
    jmp irq_common_stub

; 47: IRQ15
irq15:
    cli
    push byte 0
    push byte 15
    jmp irq_common_stub
