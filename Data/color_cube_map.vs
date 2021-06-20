// 已经废弃
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
}
vs_out;

uniform mat4 model;

void main() {
  gl_Position = model * vec4(aPosition, 1.0);
  vs_out.TexCoords = aTexCoords;
  vs_out.FragPos = vec3(model * vec4(aPosition, 1.0));
  vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
}