// player.c - 플레이어 관련 함수 구현

#include "player.h"
#include <string.h>

Player create_player(const char *name, char symbol) {
    Player p;
    strncpy(p.name, name, sizeof(p.name));
    p.name[sizeof(p.name) - 1] = '\0';
    p.symbol = symbol;
    for (int i = 0; i < 4; i++) {
        p.mals[i] = create_mal(symbol);
    }
    return p;
}

int check_win(Player player) {
    for (int i = 0; i < 4; i++) {
        if (!player.mals[i].finished) return 0;
    }
    return 1;
}