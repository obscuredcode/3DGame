//
// Created by mac on 4/23/20.
//

#include "client/render/tile/RenderCuboid.h"
#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <SDL_opengl.h>

#include <stdio.h>
#include <client/render/shader/StaticShader.h>
#include <util/Matrix.h>


void RenderCuboid::Prepare() {
    model->LoadModel();
}
void RenderCuboid::SetShader(StaticShader* shader) {
    this->shader = shader;
}

void RenderCuboid::Render(Tile tile,float r, float g, float b, float a ) {

    glUniform4f(glGetUniformLocation(shader->GetShaderId(), "ucolor" ),r,g,b,a);
    glm::mat4 trs = CalculateTRS(tile.x,tile.y,tile.z,tile.phi,tile.theta,tile.scaleX,tile.scaleY,tile.scaleZ);
    glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderId(), "u_transformation_matrix" ),1,GL_FALSE,&trs[0][0]);
    glBindVertexArray(model->VAO);
    glEnableVertexAttribArray( 0);
    //glDrawArrays(GL_TRIANGLES,0,12*3);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // GL_LINE for mesh
    glDrawElements(GL_TRIANGLES,model->GetNumberOfIndices(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
}