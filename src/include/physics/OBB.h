//
// Created by mac on 5/1/20.
//

#ifndef GAME_OBB_H
#define GAME_OBB_H

#include "BB.h"



class OBB : public BB {
    /*std::vector<Vector> Axes;
    std::vector<Vector> Vertices;*/
protected:
    void support(const BB *object, const ccd_vec3_t *dir, ccd_vec3_t *vec);
public:
    OBB() {
        type = Type::OBB;
    };
    void Build(Entity* entity);
    void Build(Tile* tile);
    bool IsIntersecting(BB* other);
    bool IsIntersecting(BB* other, CollisionData &data);


    bool TestRayOBBIntersection(glm::vec3 ray_origin, glm::vec3 ray_direction, float &intersection_distance);

    bool TestRayClosestPoint(glm::vec3 ray_origin, glm::vec3 ray_direction, float maxDistance);
};


#endif //GAME_OBB_H
