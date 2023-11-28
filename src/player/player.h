#ifndef PLAYER_H
#define PLAYER_H

enum color_e
{
    reg = 97,
    red = 31,
    blue = 34,
    purple = 35,
    cyan = 96
};

struct player_s
{
    int id;
    enum color_e color;  
};

struct player_s *create_player(int id, enum color_e color);
void destroy_player(struct player_s *player);

#endif /*!PLAYER_H*/