#version 330 core
uniform vec3 color;
out vec4 fragcolor;

in VS_OUT {
  vec3 FragPos;
  vec3 Normal;
}
fs_in;

void main() { fragcolor = vec4(color, 1.0); }