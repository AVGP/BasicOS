#include "memory.h"

void memset(unsigned char *addr, unsigned char value, unsigned int len) {
    unsigned int end_addr = addr + len;
    while(addr < end_addr) {
        *addr = value;
        addr++;
    }
}
