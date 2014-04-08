#include "screen.h"
#include "port.h"

int cursorX = 0;
int cursorY = 0;

unsigned short *video_membase = (unsigned short *)VIDEO_BASE;

void clear() {
    unsigned char *video_memory = (unsigned char *)VIDEO_BASE;
    char col = 0;
    char row = 0;
    for(row=0;row<25;row++) {
        for(col=0;col<COLS;col++) {
            *(video_memory + (row * COLS + col) * 2)     = ' ';
            *(video_memory + (row * COLS + col) * 2 + 1) = DEFAULT_STYLE;
        }
    }
    cursorX = 0;
    cursorY = 0;
    setCursor(0,0);
}

void printChar(unsigned char c) {

  if(c < ' ') {
    if(c == '\n') {
      cursorX = 0;
      cursorY++;
    }
  } else {
    unsigned char *video_memory = (unsigned char *)VIDEO_BASE;
    *(video_memory + (cursorY * COLS + cursorX) * 2)     = c;
    *(video_memory + (cursorY * COLS + cursorY) * 2 + 1) = DEFAULT_STYLE;
    cursorX++;
  }
  setCursor(cursorX, cursorY);
}

void print(unsigned char *msg) {
    while(*msg != 0) {
        if(*msg == '\n') {
          cursorY++;
          cursorX = 0;
        } else {
          printChar(*msg);
        }
        if(cursorX == 80) {
          cursorX = 0;
          cursorY++;
        }
        msg++;
    }

    setCursor(cursorX, cursorY);
}

void setCursor(int col, int row) {
    unsigned short pos = (row * COLS) + col;
    cursorX = col;
    cursorY = row;

    port_byte_out(SCREEN_CTRL_REG, 15); // Low byte of new cursor pos
    port_byte_out(SCREEN_DATA_REG, (unsigned char)(pos & 0xFF));
    port_byte_out(SCREEN_CTRL_REG, 14); // High byte of new cursor pos
    port_byte_out(SCREEN_DATA_REG, (unsigned char)((pos >> 8) & 0xFF));
}
