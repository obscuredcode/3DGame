#include <client/Game.h>
#include <iostream>
#include <filesystem>

int main(int argc, char** args) {
    std::filesystem::path working = std::filesystem::current_path();
    Game* game = Game::GetInstance();
    game->Init(working);
}

