//
// Created by mac on 4/22/20.
//


#include "client/render/model/CuboidModel.h"
#include <iostream>


#include "client/render/shader/StaticShader.h"
#include "client/render/RenderGame.h"
#define GL_GLEXT_PROTOTYPES

#include <SDL_opengl.h>

#include <stdio.h>


void CuboidModel::LoadModel() {
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&vertexBufferId);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f,
             1.0f,-1.0f,-1.0f,
             1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f,-1.0f, 1.0f,
             1.0f,-1.0f, 1.0f,
             1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
    };
    glBufferData( GL_ARRAY_BUFFER, sizeof( g_vertex_buffer_data ), g_vertex_buffer_data, GL_STATIC_DRAW );
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(float) * 3,(void *) (0)); // 4 * sizeof(float)
    glEnableVertexAttribArray( 0);
    glGenBuffers(1,&indexBuffer);
    //glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
    static const GLuint g_index_buffer_data[] = {
            0, 1, 3, 3, 1, 2,
            1, 5, 2, 2, 5, 6,
            5, 4, 6, 6, 4, 7,
            4, 0, 7, 7, 0, 3,
            3, 2, 7, 7, 2, 6,
            4, 5, 0, 0, 5, 1
    };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(g_index_buffer_data),g_index_buffer_data,GL_STATIC_DRAW);
    glGenBuffers(1,&normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,normalBuffer);
    static const GLfloat normals[] {
        0,0,1,
        1,0,0,
        0,0,-1,
        -1,0,0,
        0,1,0,
        0,-1,0
    };
    static GLfloat g_normal_buffer_data[sizeof(g_vertex_buffer_data)];
    for(int i = 0; i < 36; i++) {
        g_normal_buffer_data[i*3 + 0] = normals[g_index_buffer_data[i/6]];
        g_normal_buffer_data[i*3 + 1] = normals[g_index_buffer_data[i/6]+1];
        g_normal_buffer_data[i*3 + 2] = normals[g_index_buffer_data[i/6]+2];
        //printf("x %f, y %f, z %f\n",g_normal_buffer_data[i*3 + 0],g_normal_buffer_data[i*3 + 1],g_normal_buffer_data[i*3 + 2]);
    }
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_normal_buffer_data),g_normal_buffer_data,GL_STATIC_DRAW);
    glEnableVertexAttribArray( 1);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE,sizeof(float) * 3,(void *) 0);
    //printf("buffers cube vertex %i, index %i, normal %i\n",sizeof(g_vertex_buffer_data),sizeof(g_index_buffer_data),sizeof(g_normal_buffer_data));
}