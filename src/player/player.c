#include "player.h"

#include <stdlib.h>

struct player_s *create_player(int id, enum color_e color)
{
    struct player_s *res = malloc(sizeof(struct player_s));
    if (!res)
    {
        return NULL;
    }
    res->pin_exited = 0;
    res->spawn_tile = 4 + 9*id;
    res->pins = create_list_pin();
    res->color = color;
    res->id = id;
    return res;
}

void destroy_player(struct player_s *player)
{
    if(player)
    {
        destroy_list_pin(player->pins);
        free(player);
    }
}

void delete_pin(struct player_s *player, int nb)
{
    player->pins->nb_pin--;
    struct pin_s *tmp = player->pins->pins[nb];
    free(tmp);
    //destroy_pin(player->pins->pins[nb]);
    player->pins->pins[nb] = NULL;
}