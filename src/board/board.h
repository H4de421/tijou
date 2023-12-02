#ifndef BOARD_H 
#define BOARD_H

#include "../tiles/tiles.h" 
#include "../player/player.h"

struct board_s {
    int placed_pin;
    struct tile_s *board[36];
    struct player_s **players;
};

struct board_s *create_board(struct player_s **players);
void destroy_board(struct board_s *board);

void print_board(struct board_s *board);

void spawn_pin(struct board_s *board, int p_id);
void reset_tile(struct board_s *board,int id);
void move_pin(struct board_s *board, int pla_id, int pin_id, int off);
void is_empty(struct board_s *board, int id);
void exit_pin(struct board_s *board, int pla_id, int pin_id);
void swaps_pins(struct board_s *board, struct pin_s *pin1, struct pin_s *pin2);

void scores_sort(struct board_s *board, char tab[4]);
void print_scores(struct board_s *board);

#endif /*!BOARD_H*/