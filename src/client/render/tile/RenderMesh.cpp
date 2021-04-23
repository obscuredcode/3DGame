//
// Created by mac on 4/29/20.
//

#include "client/render/tile/RenderMesh.h"
#include "client/render/model/ComplexObjModel.h"

#define GL_GLEXT_PROTOTYPES

#include <SDL.h>
#include <SDL_opengl.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

void RenderMesh::Render(StaticShader* shader, ComplexObjModel* objModel, float x, float y, float z, float phi, float theta, float scaleX, float scaleY, float scaleZ) {
    for(int i = 0; i < objModel->meshes.size(); i++) {
        Mesh model = objModel->meshes[i];
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for (unsigned int i = 0; i < model.textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = model.textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);
            std::string uni = "material." + name + number;
            glUniform1f(glGetUniformLocation(shader->GetShaderId(), uni.c_str()), i);
            //shader.setFloat(("material" + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, model.textures[i].id);
        }
        glm::mat4 translationMatrix = glm::translate(glm::vec3(x, y, z));
        glm::mat4 rotationMatrix = glm::rotate(glm::radians(phi), glm::vec3(0, 1, 0)) *
                                   glm::rotate(glm::radians(theta), glm::vec3(0, 0, 1));
        glm::mat4 scaleMatrix = glm::scale(glm::vec3(scaleX, scaleY, scaleZ));
        glm::mat4 trs = rotationMatrix * translationMatrix * scaleMatrix;
        glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderId(), "u_transformation_matrix"), 1, GL_FALSE,
                           &trs[0][0]);
        // draw mesh
        glActiveTexture(GL_TEXTURE0);
        model.Bind();
        glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}