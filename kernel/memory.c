#include "memory.h"

void memset(void *addr, unsigned char value, unsigned int len) {
    char *end_addr = addr + len;
    char *tmp = (char *)addr;
    while(tmp < end_addr) {
        *tmp = value;
        tmp++;
    }
}

void strncpy(char *dest, char *src, int max_len) {
  int chars_copied = 0;
  while(*src != 0 || chars_copied++ < max_len) {
    *(dest++) = *(src++);
  }
  *dest = 0;
}
