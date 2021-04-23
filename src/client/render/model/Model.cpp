//
// Created by mac on 4/27/20.
//

#include "client/render/model/Model.h"

#define GL_GLEXT_PROTOTYPES

#include <SDL_opengl.h>

void Model::Destroy() {
    glDeleteBuffers(0,&vertexBufferId);
    glDeleteBuffers(0,&indexBuffer);
    glDeleteBuffers(0,&normalBuffer);
    glDeleteVertexArrays(0,&VAO);
}