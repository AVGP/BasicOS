#include "screen.h"
#include "port.h"

void clear() {
    char *video_memory = (char *)VIDEO_BASE;
    char col = 0;
    char row = 0;
    for(row=0;row<ROWS;row++) {
        for(col=0;col<COLS;col++) {
            *(video_memory + (row * COLS + col) * 2)     = ' ';
            *(video_memory + (row * COLS + col) * 2 + 1) = 0xF;
        }
    }
    setCursor(0,0);
}

void print(unsigned char *msg) {
    char *video_memory = (char *)VIDEO_BASE;
    int col = 0;
    int row = 0;
    while(*msg != 0) {
        *video_memory = *msg;
        msg++;
        video_memory += 2;
        col++;
        if(col == 80) {
            row++;
            col = 0;
        }
    }
    setCursor(col, row);
}

void setCursor(int col, int row) {
    unsigned short pos = (row * COLS) + col;

    port_byte_out(SCREEN_CTRL_REG, 15); // Low byte of new cursor pos
    port_byte_out(SCREEN_DATA_REG, (unsigned char)(pos & 0xFF));
    port_byte_out(SCREEN_CTRL_REG, 14); // High byte of new cursor pos
    port_byte_out(SCREEN_DATA_REG, (unsigned char)((pos >> 8) & 0xFF)); 
}
