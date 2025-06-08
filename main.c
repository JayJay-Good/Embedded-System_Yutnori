// main.c - 윷놀이 게임 메인 루프

#include <stdio.h>
#include "player.h"
#include "mal.h"
#include "yut_logic.h"
#include "gamecomponent.h"
#include "screen1.h"

int game_over = 0;

void switch_turn(int *turn) {
    *turn = (*turn + 1) % 2;
}

int main() {
    Player player1 = create_player("Player1", 'A');
    Player player2 = create_player("Player2", 'B');
    int turn = 0;

    while (!game_over) {
        Player *current_player = (turn == 0) ? &player1 : &player2;
        printf("\n[%s's Turn]\n", current_player->name);

        int steps = toss_yut();
        printf("You got %d steps!\n", steps);

        int piece = choose_piece(*current_player);
        move_mal(&current_player->mals[piece], steps);

        update_coords_txt();
        update_positions_from_file("coords.txt");
        bmp_read("yut_board_600x600_24bit_flipped.bmp", red_positions, blue_positions);

        if (check_win(*current_player)) {
            printf("\n== %s Wins! ==\n", current_player->name);
            game_over = 1;
        } else {
            switch_turn(&turn);
        }
    }

    return 0;
}
