//
// Created by mac on 4/29/20.
//

#ifndef GAME_RENDERMESH_H
#define GAME_RENDERMESH_H


#include "client/render/model/Mesh.h"
#include <client/render/shader/StaticShader.h>
#include <client/render/model/ComplexObjModel.h>

class RenderMesh {
    void Render(StaticShader* shader, ComplexObjModel* objModel, float x, float y, float z, float phi, float theta, float scaleX, float scaleY, float scaleZ);
};


#endif //GAME_RENDERMESH_H
