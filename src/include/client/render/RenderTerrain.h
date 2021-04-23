//
// Created by mac on 5/4/20.
//

#ifndef GAME_RENDERTERRAIN_H
#define GAME_RENDERTERRAIN_H


#include <client/render/model/TerrainMesh.h>
#include <client/render/shader/StaticShader.h>
#include <client/View.h>

class RenderTerrain {
    StaticShader* shader;
public:
    TerrainMesh* terrainMesh;
    void Prepare();
    void LoadShader(StaticShader* shader);
    void Render(float x, float y,View* view);
    RenderTerrain() {

    }
    RenderTerrain(TerrainMesh* terrainMesh) {
        this->terrainMesh = terrainMesh;
    }
};


#endif //GAME_RENDERTERRAIN_H
