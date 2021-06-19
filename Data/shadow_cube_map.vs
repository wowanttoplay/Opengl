#version 330 core
layout(location = 0) in vec3 aPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;

void main() {
  gl_Position = projection * view * model * vec4(aPosition, 1.0);
  FragPos = vec3(model * vec4(aPosition, 1.0));
}