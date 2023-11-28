CC=gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -Wvla
OBJ = board/board.o tiles/tiles.o player/player.o
TEST = test.o 

all: check

check: $(TEST) $(OBJ)
	$(CC) -o $@ $^

clean:
	$(RM) $(OBJ)
	$(RM) $(TEST)
	$(RM) check