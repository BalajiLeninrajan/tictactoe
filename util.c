#include "util.h"
#include <stdlib.h>

Board init_board(void)
{
    int **board = (int **)malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++)
    {
        board[i] = (int *)calloc(3, sizeof(int));
    }
    return board;
}

void nuke_board(Board board)
{
    for (int i = 0; i < 3; i++)
    {
        free(board[i]);
    }
    free(board);
}

Player current_player(Board board)
{
    int plays = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j])
            {
                plays++;
            }
        }
    }

    return plays % 2 == 0 ? X : O;
}

Player winner(Board board)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }

        if (board[0][i] && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    if (board[1][1] && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[1][1];
    }

    if (board[1][1] && board[2][0] == board[1][1] && board[1][1] == board[0][2])
    {
        return board[1][1];
    }

    return EMPTY;
}

bool terminal(Board board)
{
    if (winner(board))
    {
        return true;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!board[i][j])
            {
                return false;
            }
        }
    }

    return true;
}