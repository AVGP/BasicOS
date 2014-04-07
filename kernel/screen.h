#ifndef SCREEN_H_
#define SCREEN_H_

#define VIDEO_BASE 0xB8000

#define SCREEN_CTRL_REG 0x3D4
#define SCREEN_DATA_REG 0x3D5
#define DEFAULT_STYLE 0x0F


#define ROWS 25
#define COLS 80

void clear();
void setCursor(int col, int row);
void print(unsigned char *msg);
#endif
