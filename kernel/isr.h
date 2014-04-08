#ifndef ISR_H
#define ISR_H

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
#define PIC_ICW4s     0x1  // (hi) 0000 no special mode
                           // (lo) 0001 no buffering, master?, auto EOI?, 8086 mode?

typedef struct registers {
    unsigned long ds;                  // Data segment selector
    unsigned long edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    unsigned long int_no, err_code;    // Interrupt number and error code (if any)
    unsigned long eip, cs, eflags, useresp, ss; // Pushed by the processor.
} registers_t;

void setup_isrs();
void remap_pic();
void irq_handler(registers_t regs);
void exception_handler(registers_t *regs);
void setup_irq_handler(int irq, void (*handler)(registers_t *r));

#endif
