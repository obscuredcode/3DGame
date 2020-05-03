//
// Created by najimac on 5/1/20.
//

#include "physics/OBB.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/normalize_dot.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtc/quaternion.hpp>
#include <algorithm>
#include <set>
#include <glm/gtx/transform.hpp>
#include <ccd/ccd.h>
#include <ccd/quat.h>
#include <entity/Entity.h>
ccd_t ccd;

void OBB::Build(Entity* entity) {
    this->pos = entity->GetPositionVec3();
    this->rot = glm::vec3(0,glm::radians(entity->GetRotationVec3().y),0);
    this->size = glm::vec3(1,2,1);
};
void OBB::Build(Tile* tile) {
    this->pos = glm::vec3(tile->x,tile->y,tile->z);
    this->rot = glm::vec3(0,glm::radians(tile->phi),glm::radians(tile->theta));
    this->size = glm::vec3(tile->scaleX,tile->scaleY,tile->scaleZ);
    CCD_INIT(&ccd);
}
void OBB::support(const BB *object, const ccd_vec3_t *dir, ccd_vec3_t *vec) {
    ccd_vec3_t Direction;
    glm::quat quat = glm::quat(object->rot);
    ccd_quat_t qinv;
    ccdVec3Copy(&Direction,dir);
    CCD_QUAT(q,quat.x,quat.y,quat.z,quat.w);
    ccdQuatInvert2(&qinv,&q);
    ccdQuatRotVec(&Direction,&qinv);
    ccdVec3Set(vec,ccdSign(ccdVec3X(&Direction)) * object->size.x * CCD_REAL(0.5),
                   ccdSign(ccdVec3Y(&Direction)) * object->size.y * CCD_REAL(0.5),
                   ccdSign(ccdVec3Z(&Direction)) * object->size.z * CCD_REAL(0.5));
    ccdQuatRotVec(vec,&q);
    CCD_VEC3(position,object->pos.x,object->pos.y,object->pos.z);
    ccdVec3Add(vec,&position);
}
bool OBB::IsIntersecting(BB *other) {
    ccd.support1 = this->supportGlobal;
    ccd.support2 = other->supportGlobal;
    ccd.max_iterations = 100;
    int intersect = ccdGJKIntersect(this,other,&ccd);
    return intersect;
}
bool OBB::IsIntersecting(BB *other,CollisionData &data) {
    ccd.support1 = this->supportGlobal;
    ccd.support2 = other->supportGlobal;
    ccd.max_iterations = 100;
    ccd.epa_tolerance = 0.001f;
    ccd_real_t depth;
    ccd_vec3_t dir,pos;
    int intersect = ccdGJKPenetration(this,other,&ccd,&depth,&dir,&pos);
    CollisionData collisionData = CollisionData(depth,
            glm::vec3(ccdVec3X(&dir),ccdVec3Y(&dir),ccdVec3Z(&dir)),
            glm::vec3(ccdVec3X(&pos),ccdVec3Y(&pos),ccdVec3Z(&pos)));
    data = collisionData;
    return !intersect;
}