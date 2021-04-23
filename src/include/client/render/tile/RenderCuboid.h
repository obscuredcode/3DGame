//
// Created by mac on 4/23/20.
//

#ifndef GAME_RENDERCUBOID_H
#define GAME_RENDERCUBOID_H


#include <client/render/model/CuboidModel.h>
#include <client/render/shader/StaticShader.h>
#include <tile/Tile.h>

class RenderCuboid {
    Model* model;
    StaticShader* shader;
public:
    RenderCuboid() {

    }
    RenderCuboid(Model* model) {
        this->model = model;
    }
    void Prepare();
    void SetShader(StaticShader* shader);
    void Render(Tile tile,float r, float g, float b, float a );
};


#endif //GAME_RENDERCUBOID_H
