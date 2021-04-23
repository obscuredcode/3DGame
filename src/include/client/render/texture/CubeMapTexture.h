//
// Created by mac on 4/29/20.
//

#ifndef GAME_CUBEMAPTEXTURE_H
#define GAME_CUBEMAPTEXTURE_H


#include <filesystem>
#include <vector>

using Path = std::filesystem::path;

class CubeMapTexture {
    unsigned int textureID;
    Path res;

public:
    CubeMapTexture(Path resPath) {
        this->res = resPath;
    }
    void Load(std::string name,std::vector<std::string> faces);
    unsigned int GetTextureID() {return textureID;}
    void Bind();
    void Destroy();
    CubeMapTexture() {

    }
};


#endif //GAME_CUBEMAPTEXTURE_H
