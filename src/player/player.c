#include "player.h"

#include <stdlib.h>

struct player_s *create_player(int id, enum color_e color)
{
    struct player_s *res = malloc(sizeof(struct player_s));
    if (!res)
    {
        return NULL;
    }
    res->color = color;
    res->id = id;
    return res;
}

void destroy_player(struct player_s *player);