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
/*
    glm::mat4 translationMatrix = glm::translate(pos);
    glm::mat4 rotationMatrix = glm::rotate(glm::radians(tile->phi),glm::vec3(0,1,0)) * glm::rotate(glm::radians(tile->theta),glm::vec3(0,0,1));
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(tile->scaleX,tile->scaleY,tile->scaleZ));
    glm::mat4 trs = translationMatrix * rotationMatrix * scaleMatrix;
    for(unsigned int i : tile->model->normalIndices) {
        Axes.push_back(tile->model->normals[i]);
    }
    */
/*for(Vector normal : tile->model->normals) {
        Axes.push_back(Vector(trs * glm::vec4(normal,0)));
        printf("n %f, %f, %f\n",normal.x,normal.y,normal.z);
    }*//*

    for(Vector vertex : tile->model->vertices) {
        Vertices.push_back(Vector(trs * glm::vec4(vertex,0)));
        printf("v %f, %f, %f\n",vertex.x,vertex.y,vertex.z);
    }
*/

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
/*
    if(other->type == Type::OBB) {
        OBB *other = other;
        Vector relative = pos - other->pos;

        for (int iN = 0; iN < Axes.size(); iN++) {
            for (int i = 0; i < other->Vertices.size(); i++) {
                glm::proj(other->Vertices[i], Axes[iN]);
            }
        }
        for (int i = 0; i < other->Axes.size(); i++) {

        }
    }
*/
    ccd.support1 = this->supportGlobal;
    ccd.support2 = other->supportGlobal;
    ccd.max_iterations = 100;
    int intersect = ccdGJKIntersect(this,other,&ccd);
    return intersect;
}