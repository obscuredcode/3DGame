#version 150

in vec3 i_position;

out vec3 TexCoords;

uniform mat4 u_view_matrix;

void main()
{
    TexCoords = i_position;
    vec4 pos = u_view_matrix * vec4(i_position, 1.0);
    gl_Position = pos.xyww;
}