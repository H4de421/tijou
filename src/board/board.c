#include "board.h"

#include "../tiles/tiles.h" 
#include "stdio.h"
#include "stdlib.h"

static enum char_e default_board[36] ={ 
    ending, none, none, none, start, none, none, none, none,
    ending, none, none, none, start, none, none, none, none,
    ending, none, none, none, start, none, none, none, none,
    ending, none, none, none, start, none, none, none, none,
};

struct board_s *create_board(void)
{
    struct board_s *res = malloc(sizeof(struct board_s));
    if (!res)
    {
        fprintf(stderr, "ERROR malloc create board\n");
        return NULL;
    }
    res->placed_pin = 0;
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