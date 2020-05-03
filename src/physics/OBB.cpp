//
// Created by najimac on 5/1/20.
//

#include "physics/OBB.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/normalize_dot.hpp>
#include <glm/gtx/projection.hpp>
#include <algorithm>
#include <set>
#include <glm/gtx/transform.hpp>
#include <ccd/ccd.h>
void OBB::Build(Tile* tile) {
    this->pos = glm::vec3(tile->x,tile->y,tile->z);
    glm::mat4 translationMatrix = glm::translate(pos);
    glm::mat4 rotationMatrix = glm::rotate(glm::radians(tile->phi),glm::vec3(0,1,0)) * glm::rotate(glm::radians(tile->theta),glm::vec3(0,0,1));
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(tile->scaleX,tile->scaleY,tile->scaleZ));
    glm::mat4 trs = translationMatrix * rotationMatrix * scaleMatrix;
    for(unsigned int i : tile->model->normalIndices) {
        Axes.push_back(tile->model->normals[i]);
    }
    /*for(Vector normal : tile->model->normals) {
        Axes.push_back(Vector(trs * glm::vec4(normal,0)));
        printf("n %f, %f, %f\n",normal.x,normal.y,normal.z);
    }*/
    for(Vector vertex : tile->model->vertices) {
        Vertices.push_back(Vector(trs * glm::vec4(vertex,0)));
        printf("v %f, %f, %f\n",vertex.x,vertex.y,vertex.z);
    }

}
bool OBB::IsIntersecting(BB *other) {
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

    return true;
}