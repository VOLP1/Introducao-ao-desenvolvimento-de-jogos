#include "../include/Game.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        Game& game = Game::GetInstance();
        game.Run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}