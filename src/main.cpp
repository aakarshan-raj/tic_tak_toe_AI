#include "game.hpp"

int main()
{
    Game g1(3, 2, 0, 0, machine_player_type::MINIMAX, machine_player_type::CPU);
    g1.run();
    return 0;
}
