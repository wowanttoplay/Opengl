#version 330 core

in vec3 FragPos;
uniform vec3 light_position;
uniform float far_plane;

out vec4 fragcolor;

void main() {
  float light_to_frag_dis = length(light_position - FragPos);
  light_to_frag_dis = light_to_frag_dis / far_plane;
  gl_FragDepth = light_to_frag_dis;
  fragcolor = vec4(vec3(light_to_frag_dis), 1.0);
}