//
// Created by mac on 4/24/20.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/projection.hpp>
#include <client/render/tile/RenderCuboid.h>
#include <physics/OBB.h>

//#include <world/World.h>
class World;
class OBB;

class Entity {
protected:
    glm::vec3 position;
    float speed = 0.0f;
    float speedStrafe = 0.0f;
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    float headPitch = 0.0f;
public:
    OBB boundingBox;
    World *world;
    float FoV = 60.0f;

    float getHeadPitch() const;

    void setHeadPitch(float headPitch);

protected:
    float scale = 1.0f;
public:
    float maxSpeed = 10.0f;
    float maxSpeedStrafe = 5.5f;

    Entity() {

    }

    Entity(World *world, float x, float y, float z) {
        this->world = world;
        this->position = glm::vec3(x, y, z);
    }

    void SetSpeed(float speed) {
        this->speed = speed;
    }

    void SetSpeedStrafe(float speed) {
        this->speedStrafe = speed;
    }

    void SetVelocityVec3(glm::vec3 vel) {
        this->speed = vel.z;
        this->speedStrafe = vel.x;
    }

    float GetSpeed() {
        return speed;
    }

    float GetSpeedStrafe() {
        return speedStrafe;
    }

    glm::vec3 GetVelocityVec3() {
        return glm::vec3(this->speedStrafe, 0, this->speed);
    }

    void Translate(float x, float y, float z) {
        this->position.x += x;
        this->position.y += y;
        this->position.z += z;
    }

    void Translate(glm::vec3 direction) {
        this->position += direction;
    }

    void SetPosition(float x, float y, float z) {
        this->position = glm::vec3(x, y, z);
    }

    glm::vec3 GetPositionVec3() {
        return position;
    }

    glm::vec3 GetUpVec3() {
        return glm::vec3(0, 1, 0); // todo: rotation in z axis?
    }

    glm::vec3 GetDirectionVec3() {
        return glm::vec3(glm::cos(glm::radians(rotation.y)), 0, glm::sin(glm::radians(rotation.y)));
    }

    glm::vec3 GetRotationVec3() {
        return rotation;
    }

    glm::vec3 GetSizeVec3() {
        return glm::vec3(1, 1, 1); // todo: entity size;
    }

    void SetRotation(glm::vec3 direction) {
        rotation.y = glm::degrees(glm::atan(direction.x, direction.z));
    }

    void SetRotation(float phi) {
        //front = glm::rotate(front,glm::radians(phi),glm::vec3(0,1,0));
        rotation.y = phi;
    }

    float GetHeadPitch() {
        return headPitch;
    }

    void SetHeadPitch(float pitch) {
        headPitch = pitch;
    }

    virtual void Render(RenderCuboid *r);

    virtual void Update(float delta);
};


#endif //GAME_ENTITY_H
