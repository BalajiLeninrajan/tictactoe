#include "ai.h"
#include <stdio.h>
#include <stdlib.h>

Player title_screen(void);
Action get_usr_move(Board board);
void print_board(Board board);
void move(Board board, Action action);

int main(int argc, char const *argv[])
{

    Player usr_player = title_screen();
    if (!usr_player)
    {
        printf("ERROR: INVALID INPUT");
        return 1;
    }
    bool ai_turn = usr_player == X ? false : true;
    Board board = init_board();
    while (!terminal(board))
    {
        if (ai_turn)
        {
            printf("AI TURN:\n");
            Action ai_action = get_ai_move(board);
            move(board, ai_action);
            print_board(board);
        }
        else
        {
            Action usr_action = get_usr_move(board);
            move(board, usr_action);
            printf("YOUR TURN:\n");
            print_board(board);
        }
        ai_turn = !ai_turn;
    }

    printf("-----------------------\n\n");
    if (winner(board) == usr_player)
    {
        printf("YOU WIN!"); // this is useless lol
    }
    else if (winner(board))
    {
        printf("AI WINS!");
    }
    else
    {
        printf("TIE!");
    }
    printf("\n\n-----------------------\n");

    nuke_board(board);

    return 0;
}

Player title_screen(void)
{
    printf("╔════╗╔══╗╔═══╗╔════╗╔═══╗╔═══╗╔════╗╔═══╗╔═══╗\n║╔╗╔╗║╚╣╠╝║╔═╗║║╔╗╔╗║║╔═╗║║╔═╗║║╔╗╔╗║║╔═╗║║╔══╝\n╚╝║║╚╝ ║║ ║║ ╚╝╚╝║║╚╝║║ ║║║║ ╚╝╚╝║║╚╝║║ ║║║╚══╗\n  ║║   ║║ ║║ ╔╗  ║║  ║╚═╝║║║ ╔╗  ║║  ║║ ║║║╔══╝\n ╔╝╚╗ ╔╣╠╗║╚═╝║ ╔╝╚╗ ║╔═╗║║╚═╝║ ╔╝╚╗ ║╚═╝║║╚══╗\n ╚══╝ ╚══╝╚═══╝ ╚══╝ ╚╝ ╚╝╚═══╝ ╚══╝ ╚═══╝╚═══╝\n");
    printf("SELECT PLAYER (X/O): ");

    char selection;
    scanf(" %c", &selection);
    if (selection == 'X' || selection == 'x')
    {
        return X;
    }
    else if (selection == 'O' || selection == 'o')
    {
        return O;
    }
    else
    {
        return EMPTY;
    }
}

Action get_usr_move(Board board)
{
    int i, j;
    while (true)
    {
        printf("WHICH CELL YOU WOULD LIKE TO PLAY ([row], [column]): ");
        scanf("%d, %d", &i, &j);
        if (!board[i - 1][j - 1])
        {
            break;
        }
        printf("ERROR: INVALID CELL, PICK AN EMPTY CELL\n");
    }

    Action new_action = {i - 1, j - 1};
    return new_action;
}

void print_board(Board board)
{
    printf("-|-1-|-2-|-3-|\n");
    printf("1| %c | %c | %c |\n", PLR_TO_STR(board[0][0]), PLR_TO_STR(board[0][1]), PLR_TO_STR(board[0][2]));
    printf("-|---|---|---|\n");
    printf("2| %c | %c | %c |\n", PLR_TO_STR(board[1][0]), PLR_TO_STR(board[1][1]), PLR_TO_STR(board[1][2]));
    printf("-|---|---|---|\n");
    printf("3| %c | %c | %c |\n", PLR_TO_STR(board[2][0]), PLR_TO_STR(board[2][1]), PLR_TO_STR(board[2][2]));
    printf("-|---|---|---|\n");
}

void move(Board board, Action action)
{
    board[action.row][action.column] = current_player(board);
}