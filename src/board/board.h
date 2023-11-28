#ifndef BOARD_H 
#define BOARD_H

#include "../tiles/tiles.h" 

struct board_s {
    int placed_pin;
    struct tile_s *board[36];
};

struct board_s *create_board(void);
void destroy_board(struct board_s *board);

void print_board(struct board_s *board);

#endif /*!BOARD_H*/