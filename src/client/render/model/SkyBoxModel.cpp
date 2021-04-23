//
// Created by mac on 4/29/20.
//

#include "client/render/model/SkyBoxModel.h"
#define GL_GLEXT_PROTOTYPES

#include <SDL_opengl.h>

static const float SIZE = 1.0f;
void SkyBoxModel::LoadModel() {
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&vertexBufferId);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    static const float VERTICES[] = {
            -SIZE,  SIZE, -SIZE,
            -SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,

            -SIZE, -SIZE,  SIZE,
            -SIZE, -SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE,  SIZE,
            -SIZE, -SIZE,  SIZE,

            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,

            -SIZE, -SIZE,  SIZE,
            -SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE, -SIZE,  SIZE,
            -SIZE, -SIZE,  SIZE,

            -SIZE,  SIZE, -SIZE,
            SIZE,  SIZE, -SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            -SIZE,  SIZE,  SIZE,
            -SIZE,  SIZE, -SIZE,

            -SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE,  SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE,  SIZE,
            SIZE, -SIZE,  SIZE
    };
    glBufferData( GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW );
    glEnableVertexAttribArray( 0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(float) * 3,(void *) (0)); // 4 * sizeof(float)


}