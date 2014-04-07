#include "screen.h"

void main() {
    clear();
    install_idt();
    setup_isrs();

    __asm__ __volatile__ ("sti");

    print("Hello\n");
}
