//
// Created by mac on 5/1/20.
//

#ifndef GAME_TILE_H
#define GAME_TILE_H


#include <client/render/model/ObjModel.h>
#include <physics/OBB.h>
//class OBB;
class Tile {
public:
    unsigned int id;
    float x,y,z = 0;
    float scaleX,scaleY,scaleZ = 1;
    float phi,theta = 0;
    bool solid;
    glm::vec4 color;
    ObjModel* model;
    OBB bb;
    Tile() {

    }
    Tile(ObjModel* model) {
        this->model = model;
    }
    void Create(unsigned int id,float x, float y, float z, float phi, float theta, float scaleX, float scaleY, float scaleZ) {
        this->id = id;
        this->x = x;
        this->y = y;
        this->z = z;
        this->phi = phi;
        this->theta = theta;
        this->scaleX = scaleX;
        this->scaleY = scaleY;
        this->scaleZ = scaleZ;
    }
    void SetColor(float r, float g, float b, float a) {
        this->color = glm::vec4(r,g,b,a);
    }
    void BuildOBB() { bb.Build(this);}
};


#endif //GAME_TILE_H
