#version 330 core
layout(location = 0) in vec3 aPosition;

uniform mat4 Model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;

void main() {
  gl_Position = projection * view * Model * vec4(aPosition, 1.0);
  FragPos = vec3(Model * vec4(aPosition, 1.0));
}