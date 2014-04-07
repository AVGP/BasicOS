#include "memory.h"

struct idt_entry
{
    unsigned short base_lo;    // Lo word for base addr
    unsigned short sel;        // Segment selector
    unsigned char reserved;    // Always 0
    unsigned char flags;       // Flags: Present? DPL (2bit) Fixed to 01110
    unsigned short base_hi;    // Hi word for base addr
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];     // We'll fill 32, the rest is traps
struct idt_ptr idtp;

extern void load_idt();

void set_isr(unsigned char int_num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[int_num].base_lo  =  base        & 0xFFFF;
    idt[int_num].base_hi  = (base >> 16) & 0xFFFF;
    idt[int_num].sel      = sel;
    idt[int_num].reserved = 0;
    idt[int_num].flags    = flags;
}

void install_idt() {
    unsigned long idt_size = (sizeof(struct idt_entry) * 256) - 1;
    idtp.limit = idt_size;
    idtp.base  = &idt;
    memset(&idt, 0, idt_size);
    load_idt();
}
