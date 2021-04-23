#include <iostream>
#include "client/render/shader/StaticShader.h"

#include <SDL.h>
#include <SDL_opengl.h>
//#include <SDL_opengl_glext.h>
#include <GLES2/gl2.h>
#include <fstream>

//#include "GL/glew.h"

/* "#version 130\n"
                                 "in vec3 i_position;\n"
                                 "//in vec4 i_color;\n"
                                 "out vec4 v_color;\n"
                                 "uniform mat4 u_transformation_matrix;"
                                 "uniform mat4 u_projection_matrix;\n"
                                 "uniform vec4 ucolor;"
                                 "void main() {\n"
                                 "    gl_Position = u_projection_matrix * u_transformation_matrix * vec4( i_position, 1.0 );\n"
                                 "    v_color = ucolor;\n"
                                 "}\n",
                                  "#version 130\n"
                                  "in vec4 v_color;\n"
                                  "out vec4 o_color;\n"
                                  "void main() {\n"
                                  "    o_color = v_color;\n"
                                  "}\n"*/

namespace fs = std::filesystem;
void StaticShader::Load() {
    std::ifstream vert;
    std::ifstream frag;
    std::ifstream geo;
    vert.exceptions(std::ifstream::failbit| std::ifstream::badbit);
    frag.exceptions(std::ifstream::failbit| std::ifstream::badbit);
    geo.exceptions(std::ifstream::failbit| std::ifstream::badbit);
    
    try {
        fs::path v = res;
        char s[128];
        sprintf(s,"/res/shader/%s.vert",vertexName);
        fs::path path = v.concat(s);
        vert.open(path);
        std::stringstream vShaderStream;
        vShaderStream << vert.rdbuf();
        vert.close();
        vertexShaderSource = vShaderStream.str();
        sprintf(s,"/res/shader/%s.frag",fragmentName);
        fs::path f = res;
        path = f.concat(s);
        frag.open(path);
        std::stringstream  fShaderStream;
        fShaderStream << frag.rdbuf();
        frag.close();
        fragmentShaderSource = fShaderStream.str();
        if(hasGeometryShader) {
            sprintf(s,"/res/shader/%s.geo",geometryName);
            fs::path g = res;
            path = g.concat(s);
            geo.open(path);
            std::stringstream  fShaderStream;
            fShaderStream << geo.rdbuf();
            geo.close();
        }

    } catch (std::ifstream::failure e) {
        printf("%s code: %d\n",e.what(),e.code());
    }
}
void StaticShader::Build(bool withNormal) {
    int  success;
    char infoLog[512];
    const char* v = vertexShaderSource.c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&v,NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Failed to compile vertex shader: \n" << infoLog << std::endl;
    }
    const char* f = fragmentShaderSource.c_str();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &f, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Failed to compile fragment shader: \n" << infoLog << std::endl;
    }
    if(hasGeometryShader) {
        const char *g = geometryShaderSource.c_str();
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &g, NULL);
        glCompileShader(geometryShader);
        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
            std::cout << "Failed to compile geometry shader: \n" << infoLog << std::endl;
        }
    }
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    if(hasGeometryShader) glAttachShader(shaderProgram,geometryShader);
    glBindAttribLocation( shaderProgram, 0, "i_position" );
    glBindAttribLocation(shaderProgram,1,"i_normal");
    glBindAttribLocation(shaderProgram,2,"i_texture");
    //glBindAttribLocation( shaderProgram, 1, "i_color" );
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Failed to link shader: \n" << infoLog << std::endl;
    }
    //glBindAttribLocation(shaderProgram,0,"aPos");

}
GLuint StaticShader::GetShaderId() {
    return shaderProgram;
}
void StaticShader::Bind() {
    glUseProgram(shaderProgram);
}
void StaticShader::UnBind() {
    glUseProgram(0);
}
void StaticShader::Destroy() {
    UnBind();
    glDetachShader(shaderProgram,vertexShader);
    glDetachShader(shaderProgram,fragmentShader);
    if(hasGeometryShader) glDetachShader(shaderProgram,geometryShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if(hasGeometryShader) glDeleteShader(geometryShader);
    glDeleteProgram(shaderProgram);
}
void StaticShader::SetLight(GLfloat x, GLfloat y, GLfloat z,GLfloat amb, GLfloat r, GLfloat g, GLfloat b) {
    glUniform3f(glGetUniformLocation(shaderProgram, "ulightPos" ),x,y,z);
    glUniform1f(glGetUniformLocation(shaderProgram, "uambientStrength" ),amb);
    glUniform3f(glGetUniformLocation(shaderProgram, "ulightColor" ),r,g,b);
}