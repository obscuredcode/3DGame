//
// Created by mac on 4/27/20.
//

#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <cstdio>

typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef float		GLfloat;	/* single precision float */

class Model {

public:
    virtual void LoadModel() = 0;
    virtual GLuint GetNumberOfIndices() = 0;
    virtual void Destroy();
    GLuint VAO = 0;
    GLuint vertexBufferId = 0;
    GLuint indexBuffer = 0;
    GLuint normalBuffer = 0;
    Model() {

    };
};


#endif //GAME_MODEL_H
