//
// Created by mac on 4/21/20.
//

#ifndef GAME_RENDERGAME_H
#define GAME_RENDERGAME_H


#include <SDL_events.h>
#include <client/View.h>
#include "DisplayManager.h"
#include "world/World.h"

class RenderGame {
    DisplayManager* displayManager;
    StaticShader* shader;
    std::filesystem::path res;
public:
    View view;

    void Render(int fps,float delta,World* world);
    RenderGame() {

    }
    RenderGame(std::filesystem::path res,DisplayManager* displayManager) {
        this->res = res;
        this->displayManager = displayManager;
    }

    void Init(World* world);

    void Destroy();

    void KeyDown(SDL_KeyboardEvent);
};


#endif //GAME_RENDERGAME_H
