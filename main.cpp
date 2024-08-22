#include "uno_game.h"
#include <filesystem>
#include <iostream>

int main() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    UnoGame game;
    game.play();
    return 0;
}