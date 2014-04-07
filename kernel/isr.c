#include "screen.h"

typedef struct registers
{
   unsigned long ds;                  // Data segment selector
   unsigned long edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   unsigned long int_no, err_code;    // Interrupt number and error code (if applicable)
   unsigned long eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

unsigned char *exception_messages[] =
{
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

void exception_handler(registers_t *regs) {
    if (regs->int_no < 32)
    {
        print(exception_messages[r->int_no]);
        print(" That's an exception. System Halted! >:(");
        for (;;);
    }
}
