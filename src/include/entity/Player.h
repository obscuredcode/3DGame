//
// Created by najimac on 4/23/20.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include "entity/Entity.h"

class Player : public Entity {
public:
    Player() {

    }
    Player(float x, float y, float z) : Entity(x, y, z) {
    }
};


#endif //GAME_PLAYER_H
