//
// Created by mac on 5/4/20.
//

#ifndef GAME_TERRAINMESH_H
#define GAME_TERRAINMESH_H


#include <string>
#include <filesystem>
#include "Model.h"

using Path = std::filesystem::path;

class TerrainMesh : public Model {
    Path res;
    std::string name;
public:
    int yv = 10;
    void Setup();
    void Update();
    void LoadModel();
    void SetHeight(int x, int y, float height);
    GLuint GetNumberOfIndices() override;
    TerrainMesh(Path res, std::string name) {
        this->res = res;
        this->name = name;
    }
};


#endif //GAME_TERRAINMESH_H
