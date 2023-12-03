CC=gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -Wvla -g -fsanitize=address
LDFLAGS = -fsanitize=address
OBJ = board/board.o tiles/tiles.o player/player.o pin/pin.o cards/cards.o
TEST = game.o 

all: check

check: $(TEST) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ)
	$(RM) $(TEST)
	$(RM) check