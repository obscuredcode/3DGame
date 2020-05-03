#version 150 // 140
in vec4 v_color;
in vec3 fragPos;
in vec3 normal;
out vec4 o_color;
uniform vec3 ulightPos;
uniform float uambientStrength;
uniform vec3 ulightColor;
void main() {
    vec3 norm = gl_FrontFacing ? normalize(normal) : - normalize(normal);
    vec3 lightDir = normalize(ulightPos-fragPos); // todo: move to light shader
    float diff = max(dot(norm,lightDir),0);
    vec4 light = (uambientStrength + diff) * vec4(ulightColor.rgb,1);
    o_color = v_color * light;
    //if(diff == 0.0) o_color = vec4(0,1,1,1);
}