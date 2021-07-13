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

uniform mat4 Model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * Model * vec4(aPosition, 1.0);
  vs_out.TexCoords = aTexCoords;
  vs_out.FragPos = vec3(Model * vec4(aPosition, 1.0));
  vs_out.Normal = transpose(inverse(mat3(Model))) * aNormal;
}