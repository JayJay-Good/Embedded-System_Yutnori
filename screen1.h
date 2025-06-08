// screen1.h - BMP 화면 표시용 구조체 및 함수 선언

#ifndef SCREEN1_H
#define SCREEN1_H

#include <stdint.h>

typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} __attribute__((packed)) BITMAPINFOHEADER;

extern int red_positions[4][2];
extern int blue_positions[4][2];

void close_bmp(char **pDib);
void read_bmp(char *filename, char **pDib, char **data, int *cols, int *rows);
int bmp_read(char *fn, int red_position[4][2], int blue_position[4][2]);

#endif // SCREEN1_H