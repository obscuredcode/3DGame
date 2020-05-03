//
// Created by najimac on 5/2/20.
//

#ifndef GAME_BB_H
#define GAME_BB_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <vector>
#include <tile/Tile.h>
#include <entity/Entity.h>

class BB {
public:
    enum Type {
        AABB, OBB
    } type;
    virtual void Build(Tile* tile) = 0;
    virtual void Build(Entity* entity) = 0;
    virtual bool IsIntersecting(BB* other) = 0;
};
#endif //GAME_BB_H
