//
// Created by mac on 4/24/20.
//

#ifndef GAME_PLAYERINTERACTION_H
#define GAME_PLAYERINTERACTION_H

#include <SDL_events.h>
#include "entity/Player.h"

class PlayerInteraction {
    Player* player;
    int lastMouseX = 0;
    int lastMouseY = 0;
    float yaw, pitch = 0.0f;
public:
    bool thirdPersonView = false;
    PlayerInteraction() {

    }
    PlayerInteraction(Player* player) {
        this->player = player;
    }
    void MouseUpdate();
    void CheckKeys();
    void KeyDown(SDL_KeyboardEvent keyEvent);
    void KeyUp(SDL_KeyboardEvent keyEvent);

    void MouseDown(SDL_MouseButtonEvent event);
};


#endif //GAME_PLAYERINTERACTION_H
