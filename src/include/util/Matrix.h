//
// Created by mac on 5/2/20.
//

#ifndef GAME_MATRIX_H
#define GAME_MATRIX_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
static glm::mat4 CalculateTRS(float x, float y, float z, float phi, float theta, float scaleX, float scaleY, float scaleZ) {
    glm::mat4 translationMatrix = glm::translate(glm::vec3(x,y,z));
    glm::mat4 rotationMatrix = glm::rotate(glm::radians(phi),glm::vec3(0,1,0)) * glm::rotate(glm::radians(theta),glm::vec3(0,0,1));
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(scaleX,scaleY,scaleZ));
    return  translationMatrix * rotationMatrix * scaleMatrix;
}
static glm::mat4 CalculateTRS(glm::vec3 pos, glm::vec3  rot, glm::vec3 scale) {
    glm::mat4 translationMatrix = glm::translate(pos);
    glm::mat4 rotationMatrix = glm::rotate(rot.y,glm::vec3(0,1,0)) * glm::rotate(rot.z,glm::vec3(0,0,1));
    glm::mat4 scaleMatrix = glm::scale(scale);
    return  translationMatrix * rotationMatrix * scaleMatrix;
}
#endif //GAME_MATRIX_H
