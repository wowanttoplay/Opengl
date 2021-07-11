#version 330 core
uniform samplerCube cubeMap0;
out vec4 fragcolor;

in VS_OUT { vec3 Normal; }
fs_in;

void main() {
  vec3 cube_color = vec3(0.0);
  cube_color = texture(cubeMap0, fs_in.Normal).rgb;
  fragcolor = vec4(cube_color, 1.0);
}