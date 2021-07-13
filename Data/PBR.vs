#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 Model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  TexCoords = aTexCoords;
  FragPos = vec3(Model * vec4(aPosition, 1.0));
  Normal = transpose(inverse(mat3(Model))) * aNormal;

  gl_Position = projection * view * Model * vec4(aPosition, 1.0);
}