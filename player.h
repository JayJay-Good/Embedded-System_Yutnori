// player.h - 플레이어 구조체 및 관련 함수 선언

#ifndef PLAYER_H
#define PLAYER_H

#include "mal.h"

typedef struct {
    char name[20];
    char symbol;
    Mal mals[4];
} Player;

Player create_player(const char *name, char symbol);
int check_win(Player player);

#endif // PLAYER_H