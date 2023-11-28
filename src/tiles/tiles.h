#ifndef TILES_H
#define TILES_H

#include "../player/player.h"

enum char_e
{
    none = ' ',
    start = 'o',
    ending = 'x',
    pin_1 = '1',
    pin_2 = '2',
    pin_3 = '3'
};

struct tile_s
{
    int nb;
    enum char_e car;
    enum color_e color;
};

struct tile_s *create_tile(int nb, enum char_e car, enum color_e color);
void destroy_tile(struct tile_s *tile);

char *print_tile(struct tile_s *tile);

#endif /*!TILES_H*/