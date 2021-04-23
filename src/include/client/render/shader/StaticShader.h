//
// Created by mac on 4/21/20.
//

#ifndef GAME_STATICSHADER_H
#define GAME_STATICSHADER_H
#include <filesystem>
#include <string>
typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef float		GLfloat;	/* single precision float */

class StaticShader { // todo: clean up shader classes
    std::filesystem::path res;
    const char* vertexName;
    const char* fragmentName;
    const char *geometryName;
    std::string vertexShaderSource;
    unsigned int vertexShader;
    std::string fragmentShaderSource;
    unsigned int fragmentShader;
    bool hasGeometryShader = false;
    std::string geometryShaderSource;
    unsigned int geometryShader;
    GLuint shaderProgram;
public:
    StaticShader(std::filesystem::path res,const char *vertexName,const char *fragmentName) {
        this->res = res;
        this->vertexName = vertexName;
        this->fragmentName = fragmentName;
    }
    StaticShader(std::filesystem::path res,const char *vertexName,const char *fragmentName,const char *geometryName) {
        this->res = res;
        this->vertexName = vertexName;
        this->fragmentName = fragmentName;
        this->geometryName = geometryName;
        this->hasGeometryShader = true;
    }
    GLuint GetShaderId();
    void Load();
    void Build(bool withNormal);
    void Bind();
    void UnBind();
    void Destroy();
    void SetLight(GLfloat x, GLfloat y, GLfloat z,GLfloat amb, GLfloat r, GLfloat g, GLfloat b);
};

#endif //GAME_STATICSHADER_H
