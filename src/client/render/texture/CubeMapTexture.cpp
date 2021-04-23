//
// Created by mac on 4/29/20.
//

#include "client/render/texture/CubeMapTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "client/render/texture/stb_image.h"

#define GL_GLEXT_PROTOTYPES

#include <SDL_opengl.h>

void CubeMapTexture::Load(std::string name,std::vector<std::string> faces) {
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);
    int width, height, nrChannels;
    for(int i = 0; i < faces.size(); i++) {
        Path v = res;
        char s[128];
        sprintf(s,"/res/texture/%s/%s.png",name.c_str(),faces[i].c_str());
        Path path = v.concat(s);
        unsigned char *data = stbi_load(path.c_str(),&width,&height,&nrChannels,STBI_rgb_alpha);
        if(data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,
                         0,GL_RGBA,width,height,0,GL_RGBA, GL_UNSIGNED_BYTE,data
                    ); // rgb or rgba
        } else {
            printf("Cubemap texture %s failed to load at path: %s",name.c_str(),faces[i].c_str());
        }
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
void CubeMapTexture::Bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);
}

void CubeMapTexture::Destroy() {

}