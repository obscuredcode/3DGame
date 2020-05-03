#version 150
in vec3 i_position;
in vec3 i_normal;

out vec3 normal;
out vec3 fragPos;

uniform mat4 u_transformation_matrix;
uniform mat4 u_projection_matrix;

//uniform vec4 uoverrideColor;
void main() {
    vec4 worldPos = u_transformation_matrix * vec4( i_position, 1.0 );
    gl_Position = u_projection_matrix * worldPos;
    normal = mat3(transpose(inverse(u_transformation_matrix)))*i_normal;
    v_color = ucolor;
    fragPos = vec3(worldPos);
}