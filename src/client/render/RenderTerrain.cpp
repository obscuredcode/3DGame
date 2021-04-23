//
// Created by mac on 5/4/20.
//

#include <util/Matrix.h>
#include "client/render/RenderTerrain.h"
#define GL_GLEXT_PROTOTYPES

#include <SDL_opengl.h>


void RenderTerrain::Prepare() {
    terrainMesh->LoadModel();
}
void RenderTerrain::LoadShader(StaticShader *shader) {
    this->shader = shader;
}
void RenderTerrain::Render(float x, float z,View* view) {
    glm::mat4 trs = CalculateTRS(x,-3,z,0,0,1,1,1);
    glm::mat4 proj = view->GetVP();
    glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderId(), "u_projection_matrix" ), 1, GL_FALSE,
                       &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderId(), "u_transformation_matrix" ),1,GL_FALSE,&trs[0][0]);
    glBindVertexArray(terrainMesh->VAO);
    //terrainMesh->Update();

    glEnableVertexAttribArray( 0);
    glBindBuffer(GL_ARRAY_BUFFER,terrainMesh->vertexBufferId);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GL_FLOAT),0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // GL_LINE for mesh
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,terrainMesh->indexBuffer);
    glDrawElements(GL_TRIANGLES,terrainMesh->GetNumberOfIndices(),GL_UNSIGNED_INT,0);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
}