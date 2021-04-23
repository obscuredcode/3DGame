//
// Created by mac on 5/2/20.
//

#ifndef GAME_DEBUG_H
#define GAME_DEBUG_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <cstdio>
#include <util/rang.hpp>
static void PrintVec3(const char* message,glm::vec3 vec) {
    printf("%s: x %f, y %f, z %f.\n",message,vec.x,vec.y,vec.z);
}
static void PrintVec3C(const char* message,glm::vec3 vec,rang::fg color) {
    rang::setControlMode(rang::control::Force);
    std::cout << color;
    std::cout << message << ": x " << vec.x
                         << ", y " << vec.y
                         << ", z " << vec.z << ".\n";
    std::cout << rang::fg::reset;
}
#endif //GAME_DEBUG_H
