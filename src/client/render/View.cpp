//
// Created by mac on 4/24/20.
//

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <client/Game.h>

#include "client/View.h"


glm::mat4 View::ThirdPerson() {
    return glm::lookAt(
            viewerEntity->GetPositionVec3()+glm::vec3(0,10,20), // Camera is at (4,3,3), in World Space
            viewerEntity->GetPositionVec3(), // and looks at the origin
            glm::normalize(glm::vec3(0,10,20))  // Head is up (set to 0,-1,0 to look upside-down)
    );
}
glm::mat4 View::FirstPerson() {
    glm::vec3 direction = viewerEntity->GetDirectionVec3();
    direction.y = glm::sin(glm::radians(viewerEntity->GetHeadPitch()));
    return glm::lookAt(
            viewerEntity->GetPositionVec3(), // Camera is at (4,3,3), in World Space
            viewerEntity->GetPositionVec3()+direction, // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void View::RenderCamera(DisplayManager* displayManager, StaticShader* shader) {

    //glm::mat4 projectionMatrix = glm::ortho(-20.0f,20.0f,20.0f,-20.0f,-10.0f,100.0f); // In world coordinates
    projectionMatrix = glm::perspective(glm::radians(viewerEntity->FoV),
                                                  ((float) displayManager->GetWidth())/((float) displayManager->GetHeight()),nearz,farz);
    View = Game::GetInstance()->playerInteraction.thirdPersonView ? ThirdPerson() : FirstPerson();
    vp = projectionMatrix * View; // glm::rotate(View,glm::radians(-yaw),glm::vec3(0,1,0));
    glUniformMatrix4fv( glGetUniformLocation(shader->GetShaderId(), "u_projection_matrix" ), 1, GL_FALSE, &vp[0][0] );
}