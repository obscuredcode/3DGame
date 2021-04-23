//
// Created by mac on 5/1/20.
//

#include "physics/OBB.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/normalize_dot.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtc/quaternion.hpp>
#include <algorithm>
#include <set>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/closest_point.hpp>
#include <ccd/ccd.h>
#include <ccd/quat.h>
#include <entity/Entity.h>
#include <util/Matrix.h>

ccd_t ccd;

void OBB::Build(Entity* entity) {
    this->entity = entity;
    this->pos = entity->GetPositionVec3();
    this->rot = glm::vec3(0,glm::radians(entity->GetRotationVec3().y),0);
    this->size = glm::vec3(1,2,1);
};
void OBB::Build(Tile* tile) {
    this->tile = tile;
    this->pos = glm::vec3(tile->x,tile->y,tile->z);
    this->rot = glm::vec3(0,glm::radians(tile->phi),glm::radians(tile->theta));
    this->size = glm::vec3(2*tile->scaleX,tile->scaleY,tile->scaleZ);
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
    ccd_vec3_t sep;
    int intersect = ccdGJKPenetration(this,other,&ccd,&depth,&dir,&pos);
    ccdGJKSeparate(this,other,&ccd,&sep);
    CollisionData collisionData = CollisionData(depth,
            glm::vec3(ccdVec3X(&dir),ccdVec3Y(&dir),ccdVec3Z(&dir)),
            glm::vec3(ccdVec3X(&pos),ccdVec3Y(&pos),ccdVec3Z(&pos)),
            glm::vec3(ccdVec3X(&sep),ccdVec3Y(&sep),ccdVec3Z(&sep)));
    data = collisionData;
    return !intersect;
}

//http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/
float tMin = 0.0f;
float tMax = 10.0f;
bool TestAxis(glm::vec3 axis, glm::vec3 delta, glm::vec3 ray_direction, glm::vec3 aabb_min,glm::vec3 aabb_max) {
    tMin = 0.0f;
    tMax = 10.0f;
    float e = glm::dot(axis, delta);
    float f = glm::dot(ray_direction, axis);
    if ( fabs(f) > 0.001f ){

        float t1 = (e+aabb_min.y)/f;
        float t2 = (e+aabb_max.y)/f;

        if (t1>t2){float w=t1;t1=t2;t2=w;}

        if ( t2 < tMax )
            tMax = t2;
        if ( t1 > tMin )
            tMin = t1;
        if (tMin > tMax)
            return false;

    }else{
        if(-e+aabb_min.y > 0.0f || -e+aabb_max.y < 0.0f)
            return false;
    }
    return true;
}
bool OBB::TestRayOBBIntersection(	glm::vec3 ray_origin,        // Ray origin, in world space
                                     glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
                                     float& intersection_distance) {
    glm::vec3 aabb_min = -this->size;
    glm::vec3 aabb_max = this->size;
    glm::mat4 model = CalculateTRS(this->pos,this->rot,glm::vec3(1,1,1));

    glm::vec3 delta = this->pos - ray_origin;

    if(TestAxis(model[0],delta,ray_direction,aabb_min,aabb_max) &&
    TestAxis(model[1],delta,ray_direction,aabb_min,aabb_max)    &&
    TestAxis(model[2],delta,ray_direction,aabb_min,aabb_max)    ) {
        intersection_distance = tMin;
        return true;
    }
    return false;
};

float maxDistance = 10;

void supportSphere(const BB* object,const ccd_vec3_t *dir, ccd_vec3_t *vec) {
    ccdVec3Set(vec, ccdVec3X(dir)*maxDistance,ccdVec3X(dir)*maxDistance,ccdVec3X(dir)*maxDistance);
    CCD_VEC3(position,object->pos.x,object->pos.y,object->pos.z);
    ccdVec3Add(vec,&position);
}
bool OBB::TestRayClosestPoint(glm::vec3 ray_origin,        // Ray origin, in world space
                         glm::vec3 ray_direction,float maxDistance) {
    // test intersection of spheres with object over maxDistance in direction of ray
    // find closest sphere?
    // find closest sphere?
    glm::closestPointOnLine(this->pos,ray_origin,ray_direction);
}