//
// Created by mac on 5/4/20.
//

#include "client/render/model/TerrainMesh.h"
#define GL_GLEXT_PROTOTYPES

#include <SDL_opengl.h>
#include <client/render/model/ObjModel.h>

GLuint S = 10;
GLuint VERTICES = 100;

/*GLfloat vertices[3*VERTICES] = {
        -16.0f, 0.0f, 16.0f,
        -12.444445f, 0.0f, 16.0f,
        -8.888889f, 0.0f, 16.0f,
        -5.333333f, 0.0f, 16.0f,
        -1.777778f, 0.0f, 16.0f,
        1.777779f, 0.0f, 16.0f,
        5.333334f, 0.0f, 16.0f,
        8.888889f, 0.0f, 16.0f,
        12.444445f, 0.0f, 16.0f,
        16.0f, 0.0f, 16.0f,
        -16.0f, 0.0f, 12.444445f,
        -12.444445f, 0.0f, 12.444445f,
        -8.888889f, 0.0f, 12.444445f,
        -5.333333f, 0.0f, 12.444445f,
        -1.777778f, 0.0f, 12.444445f,
        1.777779f, 0.0f, 12.444445f,
        5.333334f, 0.0f, 12.444445f,
        8.888889f, 0.0f, 12.444445f,
        12.444445f, 0.0f, 12.444445f,
        16.0f, 0.0f, 12.444445f,
        -16.0f, 0.0f, 8.888889f,
        -12.444445f, 0.0f, 8.888889f,
        -8.888889f, 0.0f, 8.888889f,
        -5.333333f, 0.0f, 8.888889f,
        -1.777778f, 0.0f, 8.888889f,
        1.777779f, 0.0f, 8.888889f,
        5.333334f, 0.0f, 8.888889f,
        8.888889f, 0.0f, 8.888889f,
        12.444445f, 0.0f, 8.888889f,
        16.0f, 0.0f, 8.888889f,
        -16.0f, 0.0f, 5.333333f,
        -12.444445f, 0.0f, 5.333333f,
        -8.888889f, 0.0f, 5.333333f,
        -5.333333f, 0.0f, 5.333333f,
        -1.777778f, 0.0f, 5.333333f,
        1.777779f, 0.0f, 5.333333f,
        5.333334f, 0.0f, 5.333333f,
        8.888889f, 0.0f, 5.333333f,
        12.444445f, 0.0f, 5.333333f,
        16.0f, 0.0f, 5.333333f,
        -16.0f, 0.0f, 1.777778f,
        -12.444445f, 0.0f, 1.777778f,
        -8.888889f, 0.0f, 1.777778f,
        -5.333333f, 0.0f, 1.777778f,
        -1.777778f, 0.0f, 1.777778f,
        1.777779f, 0.0f, 1.777778f,
        5.333334f, 0.0f, 1.777778f,
        8.888889f, 0.0f, 1.777778f,
        12.444445f, 0.0f, 1.777778f,
        16.0f, 0.0f, 1.777778f,
        -16.0f, 0.0f, -1.777779f,
        -12.444445f, 0.0f, -1.777779f,
        -8.888889f, 0.0f, -1.777779f,
        -5.333333f, 0.0f, -1.777779f,
        -1.777778f, 0.0f, -1.777779f,
        1.777779f, 0.0f, -1.777779f,
        5.333334f, 0.0f, -1.777779f,
        8.888889f, 0.0f, -1.777779f,
        12.444445f, 0.0f, -1.777779f,
        16.0f, 0.0f, -1.777779f,
        -16.0f, 0.0f, -5.333334f,
        -12.444445f, 0.0f, -5.333334f,
        -8.888889f, 0.0f, -5.333334f,
        -5.333333f, 0.0f, -5.333334f,
        -1.777778f, 0.0f, -5.333334f,
        1.777779f, 0.0f, -5.333334f,
        5.333334f, 0.0f, -5.333334f,
        8.888889f, 0.0f, -5.333334f,
        12.444445f, 0.0f, -5.333334f,
        16.0f, 0.0f, -5.333334f,
        -16.0f, 0.0f, -8.888889f,
        -12.444445f, 0.0f, -8.888889f,
        -8.888889f, 0.0f, -8.888889f,
        -5.333333f, 0.0f, -8.888889f,
        -1.777778f, 0.0f, -8.888889f,
        1.777779f, 0.0f, -8.888889f,
        5.333334f, 0.0f, -8.888889f,
        8.888889f, 0.0f, -8.888889f,
        12.444445f, 0.0f, -8.888889f,
        16.0f, 0.0f, -8.888889f,
        -16.0f, 0.0f, -12.444445f,
        -12.444445f, 0.0f, -12.444445f,
        -8.888889f, 0.0f, -12.444445f,
        -5.333333f, 0.0f, -12.444445f,
        -1.777778f, 0.0f, -12.444445f,
        1.777779f, 0.0f, -12.444445f,
        5.333334f, 0.0f, -12.444445f,
        8.888889f, 0.0f, -12.444445f,
        12.444445f, 0.0f, -12.444445f,
        16.0f, 0.0f, -12.444445f,
        -16.0f, 0.0f, -16.0f,
        -12.444445f, 0.0f, -16.0f,
        -8.888889f, 0.0f, -16.0f,
        -5.333333f, 0.0f, -16.0f,
        -1.777778f, 0.0f, -16.0f,
        1.777779f, 0.0f, -16.0f,
        5.333334f, 0.0f, -16.0f,
        8.888889f, 0.0f, -16.0f,
        12.444445f, 0.0f, -16.0f,
        16.0f, 0.0f, -16.0f
};*/
std::vector<glm::vec3> vertices3;
GLfloat *vn;


void Setup() {

}
void TerrainMesh::Update() {
    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,3 * vertices3.size() * sizeof(float),NULL,GL_DYNAMIC_DRAW); // 2 *
    glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    //vn = (GLfloat*)
    glGetBufferPointerv(GL_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, reinterpret_cast<void **>(&vn));
/*    glUnmapBuffer(GL_ARRAY_BUFFER);
    glGenBuffers(1,&normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,normalBuffer);
    normals = glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);*/
    //glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,
    //        6 * sizeof(GL_FLOAT),(GLvoid*) (3 * sizeof(GL_FLOAT)));
    //glEnableVertexAttribArray(1);
    for(int i = 0; i < VERTICES; i ++) {
        vn[3*i+0] = vertices3[i].x;
        vn[3*i+1] = vertices3[i].y;
        vn[3*i+2] = vertices3[i].z;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
}
void TerrainMesh::SetHeight(int x, int y, float height) {
    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,3 * vertices3.size() * sizeof(float),0,GL_DYNAMIC_DRAW); // 2 *
    if(x > S ) x = S; if(x < 0) x = 0;
    if(y > S) y = S;  if(y < 0) y = 0;
    vn = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    int pos = x + yv * y;
    for(int i = 0; i < VERTICES; i ++) {
        vn[3*i+0] = vertices3[i].x;
        vn[3*i+1] = vertices3[i].y + i == pos ? height : 0;
        vn[3*i+2] = vertices3[i].z;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
std::vector<unsigned int> indicesVector;
int indexNo = 0;
void TerrainMesh::LoadModel() {
    //std::vector<glm::vec3> vertices3;

    ObjModel::LoadVerticesAndIndices(res,name,vertices3,indicesVector);
    indexNo = indicesVector.size();
    VERTICES = vertices3.size();
/*  for(int i = 0; i < vertices3.size(); i++) {
        vertices.push_back(vertices3[i].x);
        vertices.push_back(vertices3[i].y);
        vertices.push_back(vertices3[i].z);
    }
    VERTICES = vertices.size();*/
    S = 10; //S = std::floor(std::sqrt(VERTICES))-1;
    printf("terrain vertices: %i, s: %i, indices: %i.\n",VERTICES,S,indexNo);
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1,&indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBuffer);
    GLuint indices[indexNo];
    for(int i = 0; i < indexNo; i ++) indices[i] = indicesVector[i];
 /*   GLuint indices[] = {
            2, 11, 1, 3, 12, 2, 4, 13, 3, 5, 14, 4, 6, 15, 5, 7, 16, 6, 8, 17, 7,
            9, 18, 8, 10, 19, 9, 12, 21, 11, 13, 22, 12, 14, 23, 13, 15, 24, 14,
            16, 25, 15, 17, 26, 16, 18, 27, 17, 19, 28, 18, 20, 29, 19, 22, 31, 21,
            23, 32, 22, 24, 33, 23, 25, 34, 24, 26, 35, 25, 27, 36, 26, 28, 37, 27,
            29, 38, 28, 30, 39, 29, 32, 41, 31, 33, 42, 32, 34, 43, 33, 35, 44, 34,
            36, 45, 35, 37, 46, 36, 38, 47, 37, 39, 48, 38, 40, 49, 39, 42, 51, 41,
            43, 52, 42, 44, 53, 43, 45, 54, 44, 46, 55, 45, 47, 56, 46, 48, 57, 47,
            49, 58, 48, 50, 59, 49, 52, 61, 51, 53, 62, 52, 54, 63, 53, 55, 64, 54,
            56, 65, 55, 57, 66, 56, 58, 67, 57, 59, 68, 58, 60, 69, 59, 62, 71, 61,
            63, 72, 62, 64, 73, 63, 65, 74, 64, 66, 75, 65, 67, 76, 66, 68, 77, 67,
            69, 78, 68, 70, 79, 69, 72, 81, 71, 73, 82, 72, 74, 83, 73, 75, 84, 74,
            76, 85, 75, 77, 86, 76, 78, 87, 77, 79, 88, 78, 80, 89, 79, 82, 91, 81,
            83, 92, 82, 84, 93, 83, 85, 94, 84, 86, 95, 85, 87, 96, 86, 88, 97, 87,
            89, 98, 88, 90, 99, 89, 2, 12, 11, 3, 13, 12, 4, 14, 13, 5, 15, 14,
            6, 16, 15, 7, 17, 16, 8, 18, 17, 9, 19, 18, 10, 20, 19, 12, 22, 21,
            13, 23, 22, 14, 24, 23, 15, 25, 24, 16, 26, 25, 17, 27, 26, 18, 28,
            27, 19, 29, 28, 20, 30, 29, 22, 32, 31, 23, 33, 32, 24, 34, 33, 25,
            35, 34, 26, 36, 35, 27, 37, 36, 28, 38, 37, 29, 39, 38, 30, 40, 39,
            32, 42, 41, 33, 43, 42, 34, 44, 43, 35, 45, 44, 36, 46, 45, 37, 47,
            46, 38, 48, 47, 39, 49, 48, 40, 50, 49, 42, 52, 51, 43, 53, 52, 44,
            54, 53, 45, 55, 54, 46, 56, 55, 47, 57, 56, 48, 58, 57, 49, 59, 58,
            50, 60, 59, 52, 62, 61, 53, 63, 62, 54, 64, 63, 55, 65, 64, 56, 66,
            65, 57, 67, 66, 58, 68, 67, 59, 69, 68, 60, 70, 69, 62, 72, 71, 63,
            73, 72, 64, 74, 73, 65, 75, 74, 66, 76, 75, 67, 77, 76, 68, 78, 77,
            69, 79, 78, 70, 80, 79, 72, 82, 81, 73, 83, 82, 74, 84, 83, 75, 85,
            84, 76, 86, 85, 77, 87, 86, 78, 88, 87, 79, 89, 88, 80, 90, 89, 82,
            92, 91, 83, 93, 92, 84, 94, 93, 85, 95, 94, 86, 96, 95, 87, 97, 96,
            88, 98, 97, 89, 99, 98, 90, 100, 99
    };*/
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

    Update();


    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}



GLuint TerrainMesh::GetNumberOfIndices() {
    return indexNo;
}
