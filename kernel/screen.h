#define VIDEO_BASE 0xB8000

#define SCREEN_CTRL_REG 0x3D4
#define SCREEN_DATA_REG 0x3D5

#define ROWS 25
#define COLS 80

void clear();
void setCursor(int col, int row);
