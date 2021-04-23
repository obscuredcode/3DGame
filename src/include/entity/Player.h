//
// Created by mac on 4/23/20.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include <entity/Entity.h>

class World;

class Player : public Entity {
public:
    std::vector<std::tuple<float,Tile*>> SelectedTiles;
    Player() {

    }
    Player(World* world, float x, float y, float z) {
        this->world = world;
        this->position = glm::vec3(x,y,z);
    }
    void Update(float delta);
};


#endif //GAME_PLAYER_H
