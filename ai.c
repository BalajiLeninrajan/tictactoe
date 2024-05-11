#include "ai.h"
#include <stdlib.h>
#include <limits.h>

int min_value(Board state, int beta);
int max_value(Board state, int alpha);

Board result(Board board, Action action)
{
    int **copy = (int **)malloc(3 * sizeof(int *));
    for (int i = 0; i < 3; i++)
    {
        copy[i] = (int *)malloc(3 * sizeof(int));
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            copy[i][j] = board[i][j];
        }
    }

    copy[action.row][action.column] = current_player(board);
    return copy;
}

Action *get_actions(Board board)
{
    Action *res = (Action *)malloc(9 * sizeof(Action));
    for (int i = 0; i < 9; i++)
    {
        Action tmp = {-1, -1};
        res[i] = tmp;
    }

    int cur = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!board[i][j])
            {
                res[cur].row = i;
                res[cur].column = j;
                cur++;
            }
        }
    }

    return res;
}

int utility(Board state)
{
    return winner(state);
}

int max_value(Board state, int alpha)
{
    int v = INT_MIN;
    if (terminal(state))
    {
        return utility(state);
    }
    Action *actions = get_actions(state);
    for (int i = 0; i < 9 && actions[i].row != -1; i++)
    {
        if (alpha <= v)
            break;
        Board res = result(state, actions[i]);
        int min_state = min_value(res, v);
        nuke_board(res);
        v = v > min_state ? v : min_state;
    }
    free(actions);
    return v;
}

int min_value(Board state, int beta)
{
    int v = INT_MAX;
    if (terminal(state))
    {
        return utility(state);
    }
    Action *actions = get_actions(state);
    for (int i = 0; i < 9 && actions[i].row != -1; i++)
    {
        if (beta >= v)
            break;
        Board res = result(state, actions[i]);
        int max_state = max_value(res, v);
        nuke_board(res);
        v = v < max_state ? v : max_state;
    }
    free(actions);
    return v;
}

Action get_ai_move(Board board)
{
    Action best_action;
    if (current_player(board) == X)
    {
        int mx = INT_MIN;
        Action *actions = get_actions(board);
        for (int i = 0; i < 9 && actions[i].row != -1; i++)
        {
            Board res = result(board, actions[i]);
            int tmp = min_value(res, mx);
            nuke_board(res);
            if (tmp > mx)
            {
                mx = tmp;
                best_action.row = actions[i].row;
                best_action.column = actions[i].column;
            }
        }
        free(actions);
    }
    else
    {
        int mx = INT_MAX;
        Action *actions = get_actions(board);
        for (int i = 0; i < 9 && actions[i].row != -1; i++)
        {
            Board res = result(board, actions[i]);
            int tmp = max_value(res, mx);
            nuke_board(res);
            if (tmp < mx)
            {
                mx = tmp;
                best_action.row = actions[i].row;
                best_action.column = actions[i].column;
            }
        }
        free(actions);
    }

    return best_action;
}