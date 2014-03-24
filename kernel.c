void main() {
    char *video_memory = (char *)0xB8000;
    int col = 0;
    int row = 0;
    for(row=0;row<25;row++) {
        for(col=0;col<80;col++) {
            *(video_memory + (row * 80 + col) * 2)     = 'X';
            *(video_memory + (row * 80 + col) * 2 + 1) = 0xF;
        }
    }
}
