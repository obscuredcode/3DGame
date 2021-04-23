//
// Created by mac on 4/29/20.
//

#ifndef GAME_OBJMODEL_H
#define GAME_OBJMODEL_H
#include <filesystem>
#include <client/render/model/Model.h>
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
using Path = std::filesystem::path;

class ObjModel : public Model {
    Path res;
    std::string name;
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texUV;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> vertexIndices;
    std::vector<unsigned int> normalIndices;

    ObjModel() : Model() {
        this->name = "";
    };
    ObjModel(Path res,std::string name) : Model() {
        this->name = name;
        this->res = res;
    };
    static void LoadVerticesAndIndices(Path res, std::string name,
            std::vector<glm::vec3>& vertices,
            std::vector<unsigned int>& vertexIndices
            );
    static void LoadObj(Path res, std::string name, std::vector<glm::vec3>& vertices,
                        std::vector<glm::vec2>& texUV,
                        std::vector<glm::vec3>& normals,
                        std::vector<unsigned int>& vertexIndices,
                        std::vector<unsigned int>& normalIndices);
    void LoadModel();
    GLuint GetNumberOfIndices();
};


#endif //GAME_OBJMODEL_H
