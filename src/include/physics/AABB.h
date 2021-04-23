//
// Created by mac on 5/1/20.
//

#ifndef GAME_AABB_H
#define GAME_AABB_H


#include <util/Debug.h>
#include <physics/BB.h>

//class AABB : public BB {
//    glm::vec3 pos;
//    glm::vec3 size;
//
//public:
//    std::vector<glm::vec3> normals;
//    AABB() {
//        type = Type::AABB;
//    }
//    void Build(Entity* entity) {
//        this->pos = entity->GetPositionVec3();
//        this->size = entity->GetSizeVec3();
//    }
//    void Build(Tile* tile) {
//        this->pos = glm::vec3(tile->x,tile->y,tile->z);
//        this->size = glm::vec3(tile->scaleX,tile->scaleY,tile->scaleZ);
///*        for(glm::vec3 normal : tile->model->normals) {
//            normals.push_back(normal);
//        }*/
//    }
//    bool IsIntersecting(BB *otherBB) {
//        if(otherBB->type == Type::AABB) {
//            AABB* other = dynamic_cast<AABB *>(otherBB);
//            if( this->pos.x < other->pos.x + other->size.x &&
//                this->pos.x + this->size.x > other->pos.x  &&
//                this->pos.y < other->pos.y + other->size.y &&
//                this->pos.y + this->size.y > other->pos.y  &&
//                this->pos.z < other->pos.z + other->size.z &&
//                this->pos.z + this->size.z > other->pos.z)  {
//                //PrintVec3("AABB entity",this->pos);
//                return true;
//
//            } else return false;
//        }
//        return false;
//    }
//    bool IsIntersecting(BB *otherBB, CollisionData &data) {
//        return IsIntersecting(otherBB);
//    }
//
//};


#endif //GAME_AABB_H
