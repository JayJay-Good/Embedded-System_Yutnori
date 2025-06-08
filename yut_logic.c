// yut_logic.c - Definitions for core game logic

#include "yut_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int toss_yut() {
    srand(time(NULL));
    int sticks[4];
    int count = 0;
    for (int i = 0; i < 4; i++) {
        sticks[i] = rand() % 2;
        if (sticks[i] == 1)
            count++;
    }
    switch (count) {
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 4: return 4;
        case 0: return 5;
        default: return 0;
    }
}

int choose_piece(Player player) {
    int index = -1;
    do {
        printf("Choose a piece (0-3): ");
        scanf("%d", &index);
    } while (index < 0 || index >= 4);
    return index;
}

void move_mal(Mal *mal, int steps) {
    if (mal->finished) {
        printf("This piece has already finished.\n");
        return;
    }
    mal->position += steps;
    if (mal->position >= 20) {
        mal->finished = 1;
        mal->position = 20;
        printf("Piece reached the end!\n");
    } else {
        printf("Piece moved to position %d\n", mal->position);
    }
}