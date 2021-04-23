//
// Created by mac on 5/3/20.
//

#ifndef GAME_SOUND_H
#define GAME_SOUND_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>

class Sound {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    Sound(glm::vec3 position, glm::vec3 velocity) {
        this->position = position;
        this->velocity = velocity;
    }
};


#endif //GAME_SOUND_H
