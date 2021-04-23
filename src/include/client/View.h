//
// Created by mac on 4/24/20.
//

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <client/render/DisplayManager.h>
#include <client/render/shader/StaticShader.h>
#include <entity/Entity.h>

class View {
    glm::mat4 ThirdPerson();
    glm::mat4 FirstPerson();
    glm::mat4 View;
    glm::mat4 projectionMatrix;
    glm::mat4 vp;
public:
    float nearz = 0.1f;
    float farz = 500.0f;
    Entity* viewerEntity;
    void RenderCamera(DisplayManager* displayManager, StaticShader* shader);
    glm::mat4 GetView() { return View;}
    glm::mat4 GetProjection() { return projectionMatrix;}
    glm::mat4 GetVP() {
        return vp;
    }
};


#endif //GAME_VIEW_H
