//
// Created by mac on 4/29/20.
//

#ifndef GAME_SKYBOXMODEL_H
#define GAME_SKYBOXMODEL_H


#include <client/render/model/Model.h>

class SkyBoxModel : public Model {
public:
    void LoadModel();
    GLuint GetNumberOfIndices() {
        return 36;
    }
    SkyBoxModel() {

    };
};


#endif //GAME_SKYBOXMODEL_H
