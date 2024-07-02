#include "game.hpp"

int positions_[3][3] = {{1, 1, 1},
                        {1, 1, 1},
                        {1, 1, 0}};

int check_minimax_winner()
{
    // 8 checks

    for (int i = 0; i < 3; i++)
    {
        int z = positions_[i][0] & positions_[i][1] & positions_[i][2];
        if (z != 0)
        {
            return z == 2 ? 1 : -1;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        int z = positions_[0][i] & positions_[1][i] & positions_[2][i];
        if (z != 0)
        {
            return z == 2 ? 1 : -1;
        }
    }
    int z = positions_[0][0] & positions_[1][1] & positions_[2][2];
    if (z != 0)
    {
        return z == 2 ? 1 : -1;
    }
    int y = positions_[0][2] & positions_[1][1] & positions_[2][0];
    if (y != 0)
    {
        return z == 2 ? 1 : -1;
    }
    bool draw = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (positions_[i][j] == 0)
            {
                draw = false;
            }
        }
    }
    return draw ? 0 : 3;
}

int minimax(int depth, bool turn)
{
    int result = check_minimax_winner();
    if (result != 3)
    {
        return result;
    }
    std::cout << "Looping" << std::endl;
    if (turn)
    { // Maximising
        int best_score = -1;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (positions_[i][j] == 0)
                {
                    positions_[i][j] = 2; // AI move
                    int score = minimax(0, false);
                    positions_[i][j] = 0;
                    if (best_score < score)
                    {
                        best_score = score;
                    }
                }
            }
        }
        return best_score;
    }
    else
    { // Minimising
        int best_score = 1;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (positions_[i][j] == 0)
                {
                    positions_[i][j] = 1; // Human move
                    int score = minimax(0, false);
                    positions_[i][j] = 0;
                    if (best_score < score)
                    {
                        best_score = score;
                    }
                }
            }
        }
        return best_score;
    }
}

int main()
{
    Game g1(2,2,1,0);
    g1.run();
    return 0;
    // int x = minimax(0, true);
    // std::cout << "Static analysis:" << x << std::endl;
}
