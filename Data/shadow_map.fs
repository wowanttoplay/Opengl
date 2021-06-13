#version 330 core
in vec4 frag_pos;
uniform vec3 light_position;
uniform float far_plane;

out vec4 fragcolor;

void main() {
  float light_distance = length(frag_pos.xyz - light_position);
  light_distance = light_distance / far_plane;  // far_plane 太大会导致精度问题
  gl_FragDepth = light_distance;  //直接使用片段距离光源的距离为深度值，
}