// yut_logic.h - Declarations for core game logic

#ifndef YUT_LOGIC_H
#define YUT_LOGIC_H

#include "player.h"
#include "mal.h"

int toss_yut();
int choose_piece(Player player);
void move_mal(Mal *mal, int steps);

#endif // YUT_LOGIC_H