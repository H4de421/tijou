#include "board/board.h"

int main(void)
{
    struct board_s *test1 = create_board();
    print_board(test1);
    destroy_board(test1);
    return 0;
}