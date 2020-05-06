#version 150 // 140
in vec4 v_color;
out vec4 o_color;

float i = 0;
void main() {
    i = (sin((2*v_color.z+1)/(v_color.x+v_color.y+1))+1)/2.0;
    o_color = vec4(i+v_color.x,i*v_color.y,v_color.z,1);
    i = mod(i,1);
}