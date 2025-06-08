#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include <stdint.h>

#define BIT_VALUE_24BIT 24
#define FBDEV_FILE "/dev/fb0"

//extern int red_positions[4][2];
//extern int blue_positions[4][2];

int bmp_read(char *fn, int red_position[4][2], int blue_position[4][2]);
void update_positions_from_file(const char *filename);
void update_coords_txt();

#endif // GAMECOMPONENT_H