// gamecomponent.c - 말 좌표 파일 처리 및 화면 갱신

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gamecomponent.h"

int red_positions[4][2];
int blue_positions[4][2];

void update_coords_txt() {
    FILE *fp = fopen("coords.txt", "w");
    if (!fp) {
        perror("coords.txt write error");
        return;
    }
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d,%d/", red_positions[i][0], red_positions[i][1]);
    }
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d,%d%c", blue_positions[i][0], blue_positions[i][1], (i == 3) ? '\n' : '/');
    }
    fclose(fp);
}

void update_positions_from_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("coords.txt read error");
        return;
    }
    char coord_str[512];
    if (!fgets(coord_str, sizeof(coord_str), fp)) {
        fclose(fp);
        return;
    }
    fclose(fp);
    char *token = strtok(coord_str, "/");
    int i = 0;
    while (token != NULL && i < 8) {
        int x, y;
        sscanf(token, "%d,%d", &x, &y);
        if (i < 4) {
            red_positions[i][0] = x;
            red_positions[i][1] = y;
        } else {
            blue_positions[i - 4][0] = x;
            blue_positions[i - 4][1] = y;
        }
        i++;
        token = strtok(NULL, "/");
    }
}