//
// Created by mac on 4/20/20.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H


#include <filesystem>
#include <map>
#include <client/render/DisplayManager.h>
#include <entity/Player.h>
#include <PlayerInteraction.h>
#include <client/audio/AudioManager.h>
#include <world/World.h>
#include <client/render/RenderGame.h>

class Game {
    std::map<std::string,std::chrono::high_resolution_clock::time_point> timeprofiles;

    void Update(int fps,float delta);
    Game() {

    }
public:
    std::filesystem::path WorkingDirectory;
    PlayerInteraction playerInteraction;
    World world;
    DisplayManager displayManager;
    AudioManager audioManager;
    RenderGame renderGame;
    static Game* GetInstance();
    void Kill();
    int Init(std::filesystem::path WorkingDirectory);
    void ProfileStart(std::string Name);
    void ProfileEnd(std::string Name);
};


#endif //GAME_GAME_H
