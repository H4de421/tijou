#define NB_PLAYER 4

#include "board/board.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct player_s **players = malloc(sizeof(struct player_s) * NB_PLAYER);
    players[0] = create_player(0,red);
    players[1] = create_player(1,blue);
    players[2] = create_player(2,purple);
    players[3] = create_player(3,cyan);
    struct board_s *test1 = create_board(players);
    spawn_pin(test1, 0);
    move_pin(test1, 0, 0, 5);
    spawn_pin(test1, 3);
    move_pin(test1, 3, 0, 7);
    print_board(test1);
    swaps_pins(test1, players[0]->pins->pins[0], players[3]->pins->pins[0]);
    print_board(test1);
    move_pin(test1, 0, 0, 40);
    print_board(test1);
    /* 
    players[2]->pin_exited = 5;
    players[3]->pin_exited = 2;
    */
    print_scores(test1);
    for(int i = 0; i<4; i++)
    {
        destroy_player(players[i]);
    }
    free(players);
    destroy_board(test1);
    return 0;
}