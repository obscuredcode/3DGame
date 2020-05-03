//
// Created by najimac on 5/2/20.
//

#ifndef GAME_WORLD_H
#define GAME_WORLD_H


#include <physics/AABB.h>
#include <entity/Player.h>

class World {

public:
    Player player;
    std::vector<Tile> Tiles;
    Tile t;
    Tile teapot;
    AABB block1;
    AABB block2;
    AABB block3;
    AABB playerAABB;
    void Create();
    World() {

    };
};


#endif //GAME_WORLD_H
