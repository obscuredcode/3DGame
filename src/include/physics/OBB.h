//
// Created by najimac on 5/1/20.
//

#ifndef GAME_OBB_H
#define GAME_OBB_H

#include "BB.h"

using Vector = glm::vec3;

class OBB : public BB {
    // x, y, z
    Vector pos;
    std::vector<Vector> Axes;
    std::vector<Vector> Vertices;
public:
    OBB() {
        type = Type::OBB;
    };
    void Build(Entity* entity) {

    };
    void Build(Tile* tile);
    bool IsIntersecting(BB* other);
};


#endif //GAME_OBB_H
