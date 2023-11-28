#include "tiles.h"

#include "stdio.h"
#include "stdlib.h"

struct tile_s *create_tile(int nb, enum char_e car, enum color_e color)
{
    struct tile_s *res = malloc(sizeof(struct tile_s));
    if (!res)
    {
        fprintf(stderr, "ERROR malloc create tile\n");
    }
    res->nb = nb;
    res->car = car;
    res->color = color;
    return res;
}

void destroy_tile(struct tile_s *tile)
{
    free(tile);
}

char *print_tile(struct tile_s *tile)
{
    char *res = calloc(1,15);
    sprintf(res, "\e[%dm%c\e[0m", tile->color, tile->car);
    //sprintf(res, "%c", tile->car);
    return res;
}