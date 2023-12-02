#ifndef PLAYER_H
#define PLAYER_H

#include "../pin/pin.h"
#include "../color/color.h"

struct player_s
{
    int id;
    int spawn_tile;
    enum color_e color;
    struct liste_pin *pins;
    int pin_exited;  
};

struct player_s *create_player(int id, enum color_e color);
void destroy_player(struct player_s *player);

void delete_pin(struct player_s *player, int nb);

#endif /*!PLAYER_H*/