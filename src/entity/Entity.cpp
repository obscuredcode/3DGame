//
// Created by najimac on 4/24/20.
//

#include "entity/Entity.h"


void Entity::Update(float delta) {
    float dist = speed * delta;
    float strafe = speedStrafe * delta;
    position += dist * GetDirectionVec3() + strafe * (glm::cross(GetDirectionVec3(),GetUpVec3()));
}