#include "board.h"

#include "../tiles/tiles.h" 
#include "../color/color.h"
#include "stdio.h"
#include "stdlib.h"

static enum char_e default_board[36] ={ 
    ending, none, none, none, start, none, none, none, none,
    ending, none, none, none, start, none, none, none, none,
    ending, none, none, none, start, none, none, none, none,
    ending, none, none, none, start, none, none, none, none,
};

static int used_tiles[36] = {0};

struct board_s *create_board(struct player_s **players)
{
    struct board_s *res = malloc(sizeof(struct board_s));
    if (!res)
    {
        fprintf(stderr, "ERROR malloc create board\n");
        return NULL;
    }
    res->placed_pin = 0;
    res->players = players;
    for(int i = 0; i<36; i++)
    {
        enum color_e col = reg;
        if(i == 0 || i == 4)
        {
            col = red;
        }
        else if (i == 9 || i == 13)
        {
            col = blue;
        }
        else if (i == 18 || i == 22)
        {
            col = purple;
        }
        else if (i == 27 || i == 31)
        {
            col = cyan;
        }
        
        res->board[i] = create_tile(i, default_board[i], col);
    }
    return res;
}

void destroy_board(struct board_s *board)
{
    for(int i = 0; i<36; i++)
    {
        destroy_tile(board->board[i]);
    }
    free(board);
}

void print_board(struct board_s *board)
{
    //uper line 18 - 27
    printf("+---+-------------------------------+---+\n");
    for(int i = 27;i>=18;i--)
    {
        char *car1 = print_tile(board->board[i]);
        printf("| %s ",car1);
        free(car1);
    }
    printf("|\n+---+-------------------------------+---+\n");

    //line in between -1
    for(int line = 1; line<8; line++)
    {
        char *message = "                             ";
        char *car1 = print_tile(board->board[27+line]);
        char *car2 = print_tile(board->board[18-line]);
        printf("| %s | %s | %s |\n",
               car1,
               message,
               car2
               );
        free(car1);
        free(car2);
        printf("+---+                               +---+\n");
    }
    // last line for a well printed tab
    char *message = "                             ";
        char *car1 = print_tile(board->board[35]);
        char *car2 = print_tile(board->board[10]);
        printf("| %s | %s | %s |\n",
               car1,
               message,
               car2
               );
        free(car1);
        free(car2);
        printf("+---+-------------------------------+---+\n");

    //lower line 0 - 9
    for(int i = 0;i<=9;i++)
    {
        char *car1 = print_tile(board->board[i]);
        printf("| %s ",car1);
        free(car1);
    }
    printf("|\n+---+-------------------------------+---+\n");
}

void spawn_pin(struct board_s *board, int p_id)
{
    if(p_id>=4)
    {
        fprintf(stderr, "ERROR spawn_pin: this player doesn't exist!\n");
        return;
    }
    struct player_s *p = board->players[p_id];
    int tile_id = p->spawn_tile;
    if(p->pins->nb_pin <= 3)
    {
        int first_empty_pin = get_empty_place(p->pins);
        struct pin_s *pin = create_pin(first_empty_pin, p->color, tile_id);
        append_liste_pin(p->pins, pin);
        board->placed_pin++;
        board->board[tile_id]->color = p->color;
        board->board[tile_id]->car = pin->num + '1';
        used_tiles[tile_id] = 1;
    }
    else
    {
        printf("no more pin to spawn !\nalready %d on the board and %d exited\n", p->pins->nb_pin , p->pin_exited);
    }
}

void reset_tile(struct board_s *board,int id)
{
    board->board[id]->car = (id%9 == 0)? ending : ((id%9 == 4)? start : none);
    enum color_e col = reg;
    if(id == 0 || id == 4)
    {
        col = red;
    }
    else if (id == 9 || id == 13)
    {
        col = blue;
    }
    else if (id == 18 || id == 22)
    {
        col = purple;
    }
    else if (id == 27 || id == 31)
    {
        col = cyan;
    }
    board->board[id]->color = col;
    used_tiles[id] = 0;
}

void move_pin(struct board_s *board, int pla_id, int pin_id, int off)
{
    if (pla_id>=4)
    {
        fprintf(stderr, "ERROR move_pin: this player doesn't exist!\n");
        return;
    }
    if (pin_id>3)
    {
        fprintf(stderr, "ERROR move_pin: this pin doesn't exist!\n");
        return;
    }
    struct pin_s *pin = board->players[pla_id]->pins->pins[pin_id];
    if(pin == NULL)
    {
        fprintf(stderr, "ERROR move_pin: this pin doesn't exist!\n");
        return;
    }
    int new_id = (pin->pos + 36 + off) % 36;
    reset_tile(board, pin->pos);
    is_empty(board, new_id);
    board->board[new_id]->color = pin->color;
    board->board[new_id]->car = pin->num + '1';
    used_tiles[new_id] = 1;
    pin->pos = new_id;
}

void kill(struct board_s *board, int id)
{
    int id_players = 0;
    switch (board->board[id]->color)
    {
    case red:
        id_players = 0;
        break;
    case blue:
        id_players = 1;
        break;
    case purple:
        id_players = 2;
        break;
    case cyan:
        id_players = 3;
        break;
    default:
        printf("wrong KILL");
        break;
    }
    delete_pin(board->players[id_players], board->board[id]->car - '1');
    board->placed_pin--;
    printf("killed a tile\n");
    printf("%d remaining pin on the board\n", board->placed_pin);
}

void is_empty(struct board_s *board, int id)
{
    if (used_tiles[id])
    {
        kill(board, id);
    }
    else
    {
        printf("nothing to kill\n");
    }
}

void exit_pin(struct board_s *board, int pla_id, int pin_id)
{
    if (pla_id>=4)
    {
        fprintf(stderr, "ERROR exit_pin: this player doesn't exist!\n");
        return;
    }
    struct player_s *player = board->players[pla_id];
    if (pin_id>3)
    {
        fprintf(stderr, "ERROR exit_pin: this pin doesn't exist!\n");
        return;
    }
    struct pin_s *pin = player->pins->pins[pin_id];
    int exit_tile = (9*(pla_id))%36;
    if(exit_tile == pin->pos)
    {
        player->pin_exited++;
        reset_tile(board, pin->pos);
        pin->pos = -1;
        board->placed_pin--;
    }
    else
    {
        printf("you'r not on the right tile to exit! you are on tile nb %d\n", pin->pos);
    }
}

void scores_sort(struct board_s *board, char tab[4])
{
    int nb_swap = 1;
    int i = 0;
    while (nb_swap)
    {
        nb_swap = 0;
        for (int j = 0; j < 3; j++)
        {
            int index = tab[j] - '1';
            int index2 = tab[j+1] - '1';
            //printf("i1 = %d | i2 = %d\n", index, index2);
            if(board->players[index]->pin_exited < board->players[index2]->pin_exited)
            {
                char tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
                nb_swap++;
            }
        }
        i++;
    }
}

void print_scores(struct board_s *board)
{
    printf("\n+----------+---+\n");
    char placement[4] = {'1', '2', '3', '4'};
    scores_sort(board, placement);
    for(int i = 0; i<4; i++)
    {
        printf("| player %c | %d |\n",placement[i], board->players[placement[i] - '1']->pin_exited);
        printf("+----------+---+\n");
    }
}

void swaps_pins(struct board_s *board, struct pin_s *pin1, struct pin_s *pin2)
{
    struct tile_s *tile1 = board->board[pin1->pos];
    struct tile_s *tile2 = board->board[pin2->pos];

    // swap tiles infos
    tile1->color = pin2->color;
    tile1->car = pin2->num + '1';
    tile2->color = pin1->color;
    tile2->car = pin1->num + '1';
    // swap pin infos
    int tmp = pin1->pos;
    pin1->pos = pin2->pos;
    pin2->pos = tmp;
}

