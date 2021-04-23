//
// Created by mac on 4/24/20.
//

#include "entity/Entity.h"
#include <world/World.h>
#include <physics/OBB.h>

void Entity::Update(float delta) {
    boundingBox.Build(this);
    for(Tile tile : world->Tiles) {
        if(tile.id == 0 && !tile.solid) printf("non solid block!\n");
        OBB other = tile.bb;
        CollisionData data;
        if(tile.solid && boundingBox.IsIntersecting(&other,data)) {
            glm::vec3 velocity = GetVelocityVec3();
/*       PrintVec3("Direction",data.direction);
       PrintVec3("Pos",data.position);
       PrintVec3C("Velocity",velocity,rang::fg::red);
       printf("Collision %f!\n", data.depth);*/
            glm::vec3 alongDirection = glm::abs(glm::proj(velocity,data.direction)) * velocity;
            //glm::vec3 alongDirection = glm::proj(velocity,data.direction) * velocity;
            //velocity = velocity - 2.0f * alongDirection;
            SetVelocityVec3(glm::vec3(0,0,0));
            glm::vec3 sep = -2.0f * data.separation;// - data.depth * data.direction * 0.5f
            Translate(sep);
        }
    }
    float dist = speed * delta;
    float strafe = speedStrafe * delta;
    position += dist * GetDirectionVec3() + strafe * (glm::cross(GetDirectionVec3(),GetUpVec3()));
}