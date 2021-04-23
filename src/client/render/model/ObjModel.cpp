//
// Created by mac on 4/29/20.
//

#include <fstream>
#include <vector>
#include "client/render/model/ObjModel.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <iostream>
#include <iterator>
#include "prettyprint.hpp"

#define GL_GLEXT_PROTOTYPES

#include <SDL_opengl.h>

void ObjModel::LoadVerticesAndIndices(Path res, std::string name,
        std::vector<glm::vec3> &vertices,
        std::vector<unsigned int> &vertexIndices){
    Path v = res;
    char s[128];
    sprintf(s,"/res/model/%s.obj",name.c_str());
    Path path = v.concat(s);
    std::ifstream model;
    try{
        model.open(path,std::ios::in);
        std::string line;
        bool hasTex = false;
        bool hasNor = false;
        if(!model.is_open()) {
            printf("Cannot open model %s file %s!\n", name.c_str(), path.c_str());
            throw;
        }
        while(!std::getline(model,line).eof()) {
            //printf("read %s\n",line.c_str());
            if (line[0] == 'v') {
                if (line[1] == ' ') {
                    glm::vec3 vertex;
                    sscanf(line.c_str(), "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                    vertices.push_back(vertex);
                } else if (line[1] == 'n') {
                    hasNor = true;
                    // nothing
                } else if (line[1] == 't') {
                    hasTex = true;
                    // todo read texture coords
                }
            } else if (line[0] == 'f') {
                unsigned int i1, i2, i3;
                unsigned int iN1, iN2, iN3;
                if (hasNor && not hasTex) {
                    sscanf(line.c_str(), "f %i//%i %i//%i %i//%i\n", &i1, &iN1, &i2, &iN2, &i3, &iN3);
                } else if (hasNor && hasTex){
                    scanf(line.c_str(), "f %i/%*i/%i %i/%*i/%i %i/%*i/%i\n",&i1, &iN1, &i2, &iN2, &i3, &iN3);
                    printf("tex and normal coords found!\n");
                } else {
                    iN1 = 0;
                    iN2 = 0;
                    iN3 = 0;
                    sscanf(line.c_str(), "f %i %i %i\n", &i1, &i2, &i3);
                }
                vertexIndices.push_back(i1-1);
                vertexIndices.push_back(i2-1);
                vertexIndices.push_back(i3-1);

            } else if (line[0] == 'o' or line[0] == '#') {
                // ignore
            } else if (line[0] == 's') {

            }   else {
                //printf("Unrecognized char %s in %s.\n",path.c_str(),line[0]);
            }
            // printf("errno %i\n",errno);
        }
        model.close();
        printf("loaded %i\n",vertices.size());
    } catch (std::ifstream::failure e) {
        printf("Model %s, %s code: %d.\n",name.c_str(),e.what(),e.code());
    }
}

void ObjModel::LoadObj(Path res, std::string name, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &texUV, std::vector<glm::vec3> &normals, std::vector<unsigned int> &vertexIndices, std::vector<unsigned int> &normalIndices) {
    Path v = res;
    char s[128];
    sprintf(s,"/res/model/%s.obj",name.c_str());
    Path path = v.concat(s);
    std::ifstream model;
    try{
        model.open(path,std::ios::in);
        std::string line;
        bool hasTex = false;
        bool hasNor = false;
        if(!model.is_open()) {
            printf("Cannot open model %s file %s!\n", name.c_str(), path.c_str());
            throw;
        }
        while(!std::getline(model,line).eof()) {
            //printf("read %s\n",line.c_str());
            if (line[0] == 'v') {
                if (line[1] == ' ') {
                    glm::vec3 vertex;
                    sscanf(line.c_str(), "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                    vertices.push_back(vertex);
                } else if (line[1] == 'n') {
                    hasNor = true;
                    glm::vec3 normal;
                    sscanf(line.c_str(), "vn %f %f %f\n", &normal.x, &normal.y, &normal.z);
                    normals.push_back(normal);
                } else if (line[1] == 't') {
                    hasTex = true;
                    // todo read texture coords
                }
            } else if (line[0] == 'f') {
                unsigned int i1, i2, i3;
                unsigned int iN1, iN2, iN3;
                if (hasNor && not hasTex) {
                    sscanf(line.c_str(), "f %i//%i %i//%i %i//%i\n", &i1, &iN1, &i2, &iN2, &i3, &iN3);
                } else if (hasNor && hasTex){
                    scanf(line.c_str(), "f %i/%*i/%i %i/%*i/%i %i/%*i/%i\n",&i1, &iN1, &i2, &iN2, &i3, &iN3);
                } else {
                    iN1 = 0;
                    iN2 = 0;
                    iN3 = 0;
                    sscanf(line.c_str(), "f %i %i %i\n", &i1, &i2, &i3);
                }
                vertexIndices.push_back(i1-1);
                vertexIndices.push_back(i2-1);
                vertexIndices.push_back(i3-1);
                normalIndices.push_back(iN1-1);
                normalIndices.push_back(iN2-1);
                normalIndices.push_back(iN3-1);

            } else if (line[0] == 'o' or line[0] == '#') {
                // ignore
            } else if (line[0] == 's') {

            }   else {
                //printf("Unrecognized char %s in %s.\n",path.c_str(),line[0]);
            }
            // printf("errno %i\n",errno);
        }
        model.close();
    } catch (std::ifstream::failure e) {
        printf("Model %s, %s code: %d.\n",name.c_str(),e.what(),e.code());
    }
}

void ObjModel::LoadModel() {

    LoadObj(res,name,vertices,texUV,normals,vertexIndices,normalIndices);
    int vertexBufferSize = vertices.size() * 3;
    float vertexBuffer[vertexBufferSize];
/*    printf("vertex bufffer %i\n",vertexBufferSize);
    printf("vertices %d\n",vertices.size());
    for(int i = 0; i < vertexBufferSize; i++) {
        printf("vertex %f %f %f\n",vertices[i].x,vertices[i].y,vertices[i].z);
    }
    printf("normals %d\n",normals.size());
    for(int i = 0; i < normals.size(); i++) {
        printf("normal %f %f %f\n",normals[i].x,normals[i].y,normals[i].z);
    }
    for(int i = 0; i < vertexIndices.size(); i ++)
    {
        //printf("face %i %i %i\n",vertexIndices[i],vertexIndices[i+1],vertexIndices[i+2]);
        printf("vertex %f %f %f\n",vertices[vertexIndices[i]].x,vertices[vertexIndices[i]].y,vertices[vertexIndices[i]].z);
        printf("vertex %f %f %f\n",vertices[vertexIndices[i+1]].x,vertices[vertexIndices[i+1]].y,vertices[vertexIndices[i+1]].z);
        printf("vertex %f %f %f\n",vertices[vertexIndices[i+2]].x,vertices[vertexIndices[i+2]].y,vertices[vertexIndices[i+2]].z);
    }*/
    //printf("load vertex buffer %i\n",vertexBufferSize);
    for(int i = 0; i < vertexBufferSize/3; i++) {
        vertexBuffer[3*i + 0] = vertices[i].x;
        vertexBuffer[3*i + 1] = vertices[i].y;
        vertexBuffer[3*i + 2] = vertices[i].z;
        //printf("v %i, x %f, y %f, z %f\n",i,vertexBuffer[i*3 + 0],vertexBuffer[i*3 + 1],vertexBuffer[i*3 + 2]);
    }
    //printf("fix vertex indices\n");
/*    for (int i = 0; i < vertexIndices.size(); i++)
    {
        vertexIndices[i] = vertexIndices[i]-1;

    }*/
    float normalBuffer[normalIndices.size()*3];
    //printf("fix normal indices %i\n",normalIndices.size());
/*    for (int i = 0; i < normalIndices.size(); i++)
    {
        normalIndices[i] = normalIndices[i]-1;
    }*/
    //printf("load normal buffer %i\n",normalIndices.size() * 3);

    for (int i = 0; i < normalIndices.size(); i++) {
        normalBuffer[3*i + 0] = normals[normalIndices[i/3]].x;
        normalBuffer[3*i + 1] = normals[normalIndices[i/3]].y;
        normalBuffer[3*i + 2] = normals[normalIndices[i/3]].z;
       // printf("n %i x %f, y %f, z %f\n",3*i,normalBuffer[i*3 + 0],normalBuffer[i*3 + 1],normalBuffer[i*3 + 2]);
    }

    //printf("buffers vertex %i, index %i, normal %i\n",sizeof(vertexBuffer),vertexIndices.size(),sizeof(normalBuffer));
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&this->vertexBufferId);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,this->vertexBufferId);
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertexBuffer ), &vertexBuffer[0], GL_STATIC_DRAW );
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(float) * 3,(void *) (0));
    glEnableVertexAttribArray( 0);

    glGenBuffers(1,&this->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,vertexIndices.size()*sizeof(vertexIndices.data()),&vertexIndices.front(),GL_STATIC_DRAW);

    glGenBuffers(1,&this->normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,this->normalBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(normalBuffer),&normalBuffer[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray( 1);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE,sizeof(float) * 3,(void *) 0);
}
GLuint ObjModel::GetNumberOfIndices() {
    return vertexIndices.size();
}