#include "screen.h"


#define PIC_MASTER		0x20
#define PIC_SLAVE	 	0xA0
#define MASTER_COMMAND	PIC_MASTER
#define MASTER_DATA	  (PIC_MASTER+1)
#define SLAVE_COMMAND	PIC_SLAVE
#define SLAVE_DATA	  (PIC_SLAVE+1)

#define PIC_EOI       0x20

// Initialization word (setup)
#define PIC_ICW1      0x11 // (hi) 0001b ICW1 marker
                           // (lo) 0001b is for edge-triggered, master/slave with ICW4
                           // ICW2 is used to point to the offset in the IDT for this IRQ.

// Tell the master where the slave is connected & vice versa
#define PIC_ICW3m     0x4  // That's Interrupt Line 2 on master
#define PIC_ICW3s     0x2  // That's Interrupt Line 1 on slave

// Some more settings for the PIC
#define PIC_ICW4m     0x5  // (hi) 0000 no special mode
                           // (lo) 0101 no buffering, master?, auto EOI?, 8086 mode?
#define PIC_ICW4m     0x1  // (hi) 0000 no special mode
                           // (lo) 0001 no buffering, master?, auto EOI?, 8086 mode?

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

typedef struct registers
{
   unsigned long ds;                  // Data segment selector
   unsigned long edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   unsigned long int_no, err_code;    // Interrupt number and error code (if applicable)
   unsigned long eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

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
}

void remap_pic() {
    //Send ICW1 to the CMD ports
    port_byte_out(MASTER_COMMAND, ICW1)
    port_byte_out(SLAVE_COMMAND,  ICW1)

    //Send ICW2 to the DATA ports
    port_byte_out(MASTER_DATA, 0x20) //IRQ0  = IDT #32
    port_byte_out(SLAVE_DATA,  0x28) //IRQ8  = IDT #40

    //Send ICW3 to the DATA ports
    port_byte_out(MASTER_DATA, ICW3m)
    port_byte_out(SLAVE_DATA,  ICW3s)

    //Send ICW4 to the DATA ports
    port_byte_out(MASTER_DATA, ICW4m)
    port_byte_out(SLAVE_DATA,  ICW4s)
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
    }
}
