//
// Created by najimac on 5/2/20.
//

#ifndef GAME_DEBUG_H
#define GAME_DEBUG_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <cstdio>

static void PrintVec3(const char* message,glm::vec3 vec) {
    printf("%s: x %f, y %f, z %f.\n",message,vec.x,vec.y,vec.z);
}

#endif //GAME_DEBUG_H
