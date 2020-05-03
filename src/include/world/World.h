//
// Created by najimac on 5/2/20.
//

#ifndef GAME_WORLD_H
#define GAME_WORLD_H


#include <physics/AABB.h>
#include <entity/Player.h>
#include <physics/OBB.h>

class World {

public:
    Player player;
    std::vector<Tile> Tiles;
    Tile t;
    Tile teapot;
    AABB block1;
    AABB block2;
    OBB block3;
    OBB playerAABB;
    void Create();
    World() {

    };
};


#endif //GAME_WORLD_H
