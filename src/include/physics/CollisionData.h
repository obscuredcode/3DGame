//
// Created by najimac on 5/3/20.
//

#ifndef GAME_COLLISIONDATA_H
#define GAME_COLLISIONDATA_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

class CollisionData {
public:
    float depth;
    glm::vec3 direction;
    glm::vec3 position;
    CollisionData() {

    }
    CollisionData(float depth, glm::vec3 direction, glm::vec3 position) {
        this->depth = depth;
        this->direction = direction;
        this->position = position;
    }
};
#endif //GAME_COLLISIONDATA_H
