#include <client/Game.h>
#include <iostream>
#include <filesystem>
#include <AL/alut.h>

int main(int argc, char** args) {
    std::filesystem::path working = std::filesystem::current_path();
    alutInit(&argc,args);
    Game* game = Game::GetInstance();
    game->Init(working);
}

