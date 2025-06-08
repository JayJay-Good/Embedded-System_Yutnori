#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <string.h>
#include "screen1.h"

#define BIT_VALUE_24BIT 24
#define FBDEV_FILE "/dev/fb0"

//int red_positions[4][2];
//int blue_positions[4][2];

void close_bmp(char **pDib) {
    free(*pDib);
}

void read_bmp(char *filename, char **pDib, char **data, int *cols, int *rows) {
    BITMAPFILEHEADER bmpHeader;
    BITMAPINFOHEADER *bmpInfoHeader;
    unsigned int size;
    unsigned char magicNum[2];
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen");
        return;
    }

    magicNum[0] = fgetc(fp);
    magicNum[1] = fgetc(fp);
    if (magicNum[0] != 'B' || magicNum[1] != 'M') {
        printf("Not a BMP file!\n");
        fclose(fp);
        return;
    }

    fread(&bmpHeader.bfSize, 1, sizeof(BITMAPFILEHEADER), fp);
    size = bmpHeader.bfSize - sizeof(BITMAPFILEHEADER);
    *pDib = (unsigned char *)malloc(size);
    fread(*pDib, 1, size, fp);
    bmpInfoHeader = (BITMAPINFOHEADER *)*pDib;

    if (bmpInfoHeader->biBitCount != BIT_VALUE_24BIT) {
        printf("Only 24-bit BMP supported\n");
        fclose(fp);
        return;
    }

    *cols = bmpInfoHeader->biWidth;
    *rows = bmpInfoHeader->biHeight;
    *data = (char *)(*pDib + bmpHeader.bfOffBits - sizeof(BITMAPFILEHEADER) - 2);
    fclose(fp);
}

static void draw_filled_circle(uint32_t *fb_pixels, int fb_width, int fb_height,
                               int cx, int cy, int r, uint32_t color) {
    for (int dy = -r; dy <= r; dy++) {
        for (int dx = -r; dx <= r; dx++) {
            if (dx * dx + dy * dy <= r * r) {
                int x = cx + dx;
                int y = cy + dy;
                if (x >= 0 && x < fb_width && y >= 0 && y < fb_height) {
                    fb_pixels[y * fb_width + x] = color;
                }
            }
        }
    }
}

int bmp_read(char *fn, int red_position[4][2], int blue_position[4][2]) {
    int fb_fd = open(FBDEV_FILE, O_RDWR);
    if (fb_fd < 0) {
        perror("fb open error");
        return -1;
    }

    struct fb_var_screeninfo fbvar;
    if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &fbvar)) {
        perror("fb ioctl error");
        close(fb_fd);
        return -1;
    }

    int fb_width = fbvar.xres;
    int fb_height = fbvar.yres;
    int fb_size = fb_width * fb_height * 4;

    uint32_t *fb_pixels = mmap(0, fb_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
    if ((int)fb_pixels == -1) {
        perror("mmap error");
        close(fb_fd);
        return -1;
    }

    char *pData = NULL, *data = NULL;
    int cols, rows;

    read_bmp(fn, &pData, &data, &cols, &rows);

    int draw_cols = (cols > fb_width) ? fb_width : cols;
    int draw_rows = (rows > fb_height) ? fb_height : rows;

    for (int y = 0; y < draw_rows; y++) {
        for (int x = 0; x < draw_cols; x++) {
            int b = data[y * cols * 3 + x * 3 + 0];
            int g = data[y * cols * 3 + x * 3 + 1];
            int r = data[y * cols * 3 + x * 3 + 2];
            fb_pixels[y * fb_width + x] = (r << 16) | (g << 8) | b;
        }
    }

    for (int i = 0; i < 4; i++) {
        draw_filled_circle(fb_pixels, fb_width, fb_height, red_position[i][0], red_position[i][1], 20, 0xFF0000);
        draw_filled_circle(fb_pixels, fb_width, fb_height, blue_position[i][0], blue_position[i][1], 20, 0x0000FF);
    }

    close_bmp(&pData);
    munmap(fb_pixels, fb_size);
    close(fb_fd);
    return 0;
}

//int main(int argc, char *argv[]) {
//    if (argc != 2) {
//        printf("Usage: %s <bmp_file>\n", argv[0]);
//        return -1;
//    }

//    char *bmp_file = argv[1];

//    while (1) {
//        FILE *fp = fopen("coords.txt", "r");
//        if (!fp) {
//            perror("coords.txt open error");
//            sleep(1);
//            continue;
//        }

//        char coord_str[512];
//        if (!fgets(coord_str, sizeof(coord_str), fp)) {
//            fclose(fp);
//            sleep(1);
//            continue;
//        }
//        fclose(fp);

//        char *token = strtok(coord_str, "/");
//        int i = 0;
//        while (token != NULL && i < 8) {
//            int x, y;
//            sscanf(token, "%d,%d", &x, &y);
//            if (i < 4) {
//                red_positions[i][0] = x;
//                red_positions[i][1] = y;
//            } else {
//                blue_positions[i - 4][0] = x;
//                blue_positions[i - 4][1] = y;
//            }
//            i++;
//            token = strtok(NULL, "/");
//        }

//        if (i == 8) {
//            bmp_read(bmp_file, red_positions, blue_positions);
//        } else {
//            printf("Invalid coordinate count in coords.txt\n");
//        }

//        sleep(1);
//    }

//    return 0;
//}
