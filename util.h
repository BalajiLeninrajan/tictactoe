#include <stdbool.h>

typedef struct Action
{
    int row;
    int column;
} Action;

typedef int **Board;

typedef int Player;
#define X 1
#define O -1
#define EMPTY 0
#define PLR_TO_STR(player) player == X ? 'X' : (player == O ? 'O' : ' ')

Board init_board(void);

Player current_player(Board board);

bool terminal(Board board);

Player winner(Board Board);

void nuke_board(Board board);