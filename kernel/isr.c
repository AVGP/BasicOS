#include "isr.h"
#include "port.h"

void *irq_handlers[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// I kinda miss the messy ways of interpreted languages here...
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void setup_isrs() {
    set_isr(0, (unsigned)isr0, 0x08, 0x8E);
    set_isr(1, (unsigned)isr1, 0x08, 0x8E);
    set_isr(2, (unsigned)isr2, 0x08, 0x8E);
    set_isr(3, (unsigned)isr3, 0x08, 0x8E);
    set_isr(4, (unsigned)isr4, 0x08, 0x8E);
    set_isr(5, (unsigned)isr5, 0x08, 0x8E);
    set_isr(6, (unsigned)isr6, 0x08, 0x8E);
    set_isr(7, (unsigned)isr7, 0x08, 0x8E);

    set_isr(8, (unsigned)isr8, 0x08, 0x8E);
    set_isr(9, (unsigned)isr9, 0x08, 0x8E);
    set_isr(10, (unsigned)isr10, 0x08, 0x8E);
    set_isr(11, (unsigned)isr11, 0x08, 0x8E);
    set_isr(12, (unsigned)isr12, 0x08, 0x8E);
    set_isr(13, (unsigned)isr13, 0x08, 0x8E);
    set_isr(14, (unsigned)isr14, 0x08, 0x8E);
    set_isr(15, (unsigned)isr15, 0x08, 0x8E);

    set_isr(16, (unsigned)isr16, 0x08, 0x8E);
    set_isr(17, (unsigned)isr17, 0x08, 0x8E);
    set_isr(18, (unsigned)isr18, 0x08, 0x8E);
    set_isr(19, (unsigned)isr19, 0x08, 0x8E);
    set_isr(20, (unsigned)isr20, 0x08, 0x8E);
    set_isr(21, (unsigned)isr21, 0x08, 0x8E);
    set_isr(22, (unsigned)isr22, 0x08, 0x8E);
    set_isr(23, (unsigned)isr23, 0x08, 0x8E);

    set_isr(24, (unsigned)isr24, 0x08, 0x8E);
    set_isr(25, (unsigned)isr25, 0x08, 0x8E);
    set_isr(26, (unsigned)isr26, 0x08, 0x8E);
    set_isr(27, (unsigned)isr27, 0x08, 0x8E);
    set_isr(28, (unsigned)isr28, 0x08, 0x8E);
    set_isr(29, (unsigned)isr29, 0x08, 0x8E);
    set_isr(30, (unsigned)isr30, 0x08, 0x8E);
    set_isr(31, (unsigned)isr31, 0x08, 0x8E);

    remap_pic();

    set_isr(32, (unsigned)irq0,  0x08, 0x8E);
    set_isr(33, (unsigned)irq1,  0x08, 0x8E);
    set_isr(34, (unsigned)irq2,  0x08, 0x8E);
    set_isr(35, (unsigned)irq3,  0x08, 0x8E);
    set_isr(36, (unsigned)irq4,  0x08, 0x8E);
    set_isr(37, (unsigned)irq5,  0x08, 0x8E);
    set_isr(38, (unsigned)irq6,  0x08, 0x8E);
    set_isr(39, (unsigned)irq7,  0x08, 0x8E);
    set_isr(40, (unsigned)irq8,  0x08, 0x8E);
    set_isr(41, (unsigned)irq9,  0x08, 0x8E);
    set_isr(42, (unsigned)irq10, 0x08, 0x8E);
    set_isr(43, (unsigned)irq11, 0x08, 0x8E);
    set_isr(44, (unsigned)irq12, 0x08, 0x8E);
    set_isr(45, (unsigned)irq13, 0x08, 0x8E);
    set_isr(46, (unsigned)irq14, 0x08, 0x8E);
    set_isr(47, (unsigned)irq15, 0x08, 0x8E);
}

void remap_pic() {
    //Send ICW1 to the CMD ports
    port_byte_out(MASTER_COMMAND, PIC_ICW1);
    port_byte_out(SLAVE_COMMAND,  PIC_ICW1);

    //Send ICW2 to the DATA ports
    port_byte_out(MASTER_DATA, 0x20); //IRQ0  = IDT #32
    port_byte_out(SLAVE_DATA,  0x28); //IRQ8  = IDT #40

    //Send ICW3 to the DATA ports
    port_byte_out(MASTER_DATA, PIC_ICW3m);
    port_byte_out(SLAVE_DATA,  PIC_ICW3s);

    //Send ICW4 to the DATA ports
    port_byte_out(MASTER_DATA, PIC_ICW4m);
    port_byte_out(SLAVE_DATA,  PIC_ICW4s);

    //Unmask ALL the IRQs!
    port_byte_out(MASTER_DATA, 0);
    port_byte_out(SLAVE_DATA,  0);
}

void setup_irq_handler(int irq, void (*handler)(registers_t *r)) {
  irq_handlers[irq] = handler;
}

void irq_handler(registers_t regs) {
    void (*handler)(struct registers *r) = irq_handlers[regs.int_no];

    if(handler != 0) {
      handler(&regs);
    }

    //Did this come from the slave PIC?
    if (regs.int_no >= 8) {
        port_byte_out(SLAVE_COMMAND, PIC_EOI);
    }

    port_byte_out(MASTER_COMMAND, PIC_EOI);
}

void exception_handler(registers_t *regs) {
    char *exception_messages[] = {
        "Divide by Zero you mustn't (Division By Zero)",
        "They see me debugging, they interruptin' (Debugger exception)",
        "We can't mask here, this is Interrupt country! (Non-maskable Interrupt)",
        "Breakpoint. Kthxbye. (Breakpoint exception)",
        "Variables overflowing... (Into detected overflow)",
        "Out of Bounds, man. (Out of bounds)",
        "Speak the language of my people! (Invalid opcode)",
        "No Coprocessor. You're alone here.",

        "Double Fault, double fun!",
        "Coprocessor.. what you doin'? Coprocessor.. stahp! (Coprocessor Segment Overrun)",
        "Bad TSS. Bad. Don't do that.",
        "Use segments they said, they'll be present they said.",
        "Stack Fault. Better clean up that mess.",
        "General Protection Fault orders: You shall not pass!",
        "Page Fault - try a bigger book.",
        "I have no idea what you're interruptin' about... (Unknown interrupt)",

        "Coprocessor Fault. Not pointing any fingers, tho.",
        "Alignment Check - get your shit in line...",
        "Machine Check - Skynet has become self aware. Run!",
        "Nothing to see here, yet you read me. Bad, huh? (I)",
        "Nothing to see here, yet you read me. Bad, huh? (II)",
        "Nothing to see here, yet you read me. Bad, huh? (III)",
        "Nothing to see here, yet you read me. Bad, huh? (IV)",
        "Nothing to see here, yet you read me. Bad, huh? (V)",

        "Nothing to see here, yet you read me. Bad, huh? (VI)",
        "Nothing to see here, yet you read me. Bad, huh? (VII)",
        "Nothing to see here, yet you read me. Bad, huh? (IIX)",
        "Nothing to see here, yet you read me. Bad, huh? (IX)",
        "Nothing to see here, yet you read me. Bad, huh? (X)",
        "Nothing to see here, yet you read me. Bad, huh? (XI)",
        "Nothing to see here, yet you read me. Bad, huh? (XII)",
        "Nothing to see here, yet you read me. Bad, huh? (XIIV)"
    };

    if (regs->int_no < 32)
    {

        print(exception_messages[regs->int_no]);
        print("\nThat's an exception. System Halted! >:(");
        for (;;);
    } else {
      print("Weird exception @.@");
    }
}
