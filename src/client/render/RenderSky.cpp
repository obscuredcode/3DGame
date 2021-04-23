//
// Created by mac on 4/29/20.
//

#include <client/render/texture/CubeMapTexture.h>
#include "client/render/RenderSky.h"
#define GL_GLEXT_PROTOTYPES

#include <SDL_opengl.h>

#include <stdio.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <client/render/model/SkyBoxModel.h>
#include <client/Game.h>

SkyBoxModel skyBoxModel;
CubeMapTexture skyCubeMap;
StaticShader* shader;

void RenderSky::Init() {

    shader = new StaticShader(res,"sky","sky");
    shader->Load();
    shader->Build(false);
    skyBoxModel.LoadModel();
    Game::GetInstance()->ProfileStart("Loading Sky CubeMap");
    skyCubeMap = CubeMapTexture(res);
    std::vector<std::string> faces
    {
        "right",
        "left",
        "top",
        "bottom",
        "back",
        "front"
    };
    skyCubeMap.Load("sky",faces);
    Game::GetInstance()->ProfileEnd("Loading Sky CubeMap");
}
void RenderSky::Render(int fps, float delta) {
    //glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    shader->Bind();
    //glm::mat4 inverseView = glm::inverse(view->GetView());
    //glm::mat4 matrix = glm::mat4(glm::mat3(inverseView));
    //glm::mat4 viewMatrix = glm::inverse(view->GetProjection() * matrix);
    glm::mat4 viewMatrix = glm::mat4(glm::mat3(view->GetVP()));
    glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderId(), "u_view_matrix" ), 1, GL_FALSE,
                       &viewMatrix[0][0]);
    glUniform1i(glGetUniformLocation(shader->GetShaderId(),"skybox"),0);
    skyCubeMap.Bind();
    glBindVertexArray(skyBoxModel.VAO);
    glEnableVertexAttribArray( 0);
    glDrawArrays(GL_TRIANGLES,0,36);
    glDisableVertexAttribArray( 0);
    glBindVertexArray(0);
    shader->UnBind();
    glDepthFunc(GL_LESS);
    //glDepthMask(GL_TRUE);
}
void RenderSky::Destroy() {
    shader->UnBind();
}