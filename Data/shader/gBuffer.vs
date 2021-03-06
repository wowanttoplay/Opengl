
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT {
  vec3 position;
  vec3 normal;
  vec2 uv;
}
vs_out;

void main() {
  gl_Position = projection * view * model * vec4(aPos, 1.0);

  vs_out.position = vec3(view * model * vec4(aPos, 1.0));
  vs_out.normal = transpose(inverse(mat3(view * model))) * aNormal;
  vs_out.uv = aTexCoords;
}