#include <iostream>

#include "Game.hpp"

#include <cstdio>

int main()
{


    std::cout << "Starting Game" << std::endl;

    Game game;
    game.build();
    game.run();
    game.stop();
	return 0;
}

