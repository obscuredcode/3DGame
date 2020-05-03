#version 150
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
    FragColor = (texture(skybox, TexCoords));// + texture(skybox, TexCoords+vec3(0,1,1))+ texture(skybox, TexCoords+vec3(1,0,1))+ texture(skybox, TexCoords+vec3(1,1,1))+ texture(skybox, TexCoords+vec3(0,-1,1))+ texture(skybox, TexCoords+vec3(-1,0,1))+ texture(skybox, TexCoords+vec3(-1,-1,1)))/6;
}
