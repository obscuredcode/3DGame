//
// Created by mac on 5/2/20.
//

#ifndef GAME_BB_H
#define GAME_BB_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <vector>
//#include <tile/Tile.h>
//#include <entity/Entity.h>

#include <ccd/vec3.h>
#include <physics/CollisionData.h>
#include <cstdio>

class Entity;
class Tile;

class BB {
    using Vector = glm::vec3;
protected:
    static void supportGlobal(const void *obj, const ccd_vec3_t *dir, ccd_vec3_t *vec);
    virtual void support(const BB * object, const ccd_vec3_t *dir, ccd_vec3_t *vec) {
        printf("CCD support not setup for BB type %s.\n", type == OBB ? "OBB" : "AABB");
    };
public:
    Vector pos;
    Vector rot;
    Vector size;
    Tile* tile;
    Entity* entity;
    enum Type {
        AABB, OBB
    } type;
    virtual void Build(Tile* tile) = 0;
    virtual void Build(Entity* entity) = 0;
    virtual bool IsIntersecting(BB* other) = 0;
    virtual bool IsIntersecting(BB* other, CollisionData &data) = 0;
};
#endif //GAME_BB_H
