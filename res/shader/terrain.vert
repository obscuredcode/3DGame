#version 150

in vec3 i_position;
out vec4 v_color;
uniform mat4 u_transformation_matrix;
uniform mat4 u_projection_matrix;


void main() {
    vec4 worldPos = u_transformation_matrix * vec4( i_position, 1.0 );
    gl_Position = u_projection_matrix * worldPos;
    v_color = worldPos;
}