//
// Created by mac on 5/2/20.
//

#ifndef GAME_WORLD_H
#define GAME_WORLD_H


#include <physics/AABB.h>
#include <physics/OBB.h>

#include <entity/Player.h>
#include <client/audio/Sound.h>
//class Entity;
//class Player;

class World {
public:
    Player player;
    mutable std::vector<Tile> Tiles;
    std::vector<OBB> StaticBBs;
    std::vector<Entity> Entities;
    Tile t;
    Tile teapot;
    OBB playerAABB;
    void Create();
    void PlaySound(Sound sound);
    void Update(float delta);
    World() {
    }
    void SetSolid(int no, bool solid) {Tiles[no].solid = solid;} // TODO: UNSAFE!
    void SetColor(int no, float color) {Tiles[no].color.w = color;} // TODO: UNSAFE!
};


#endif //GAME_WORLD_H
