#include "memory.h"

void memset(void *addr, unsigned char value, unsigned int len) {
    unsigned int end_addr = addr + len;
    char *tmp = (char *)addr;
    while(tmp < end_addr) {
        *tmp = value;
        tmp++;
    }
}
