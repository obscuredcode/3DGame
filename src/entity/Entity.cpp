//
// Created by najimac on 4/24/20.
//

#include "entity/Entity.h"
#include <world/World.h>
#include <physics/OBB.h>

void Entity::Update(float delta) {
    boundingBox.Build(this);
    for(OBB obb : world->StaticBBs) {
        OBB other = obb;
        CollisionData data;
        if(boundingBox.IsIntersecting(&other,data)) {
            glm::vec3 velocity = GetVelocityVec3();
/*       PrintVec3("Direction",data.direction);
       PrintVec3("Pos",data.position);
       PrintVec3C("Velocity",velocity,rang::fg::red);
       printf("Collision %f!\n", data.depth);*/
            glm::vec3 alongDirection = glm::abs(glm::proj(velocity,data.direction)) * velocity;
            //glm::vec3 alongDirection = glm::proj(velocity,data.direction) * velocity;
            velocity = velocity - 2.0f * alongDirection;
            SetVelocityVec3(velocity);
            Translate(- data.depth * data.direction * 0.5f);
        }
    }
    float dist = speed * delta;
    float strafe = speedStrafe * delta;
    position += dist * GetDirectionVec3() + strafe * (glm::cross(GetDirectionVec3(),GetUpVec3()));
}