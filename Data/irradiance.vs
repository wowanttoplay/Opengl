#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 localPosition;

uniform mat4 projection;
uniform mat4 view;

void main() {
  localPosition = aPosition;
  gl_Position = projection * view * vec4(aPosition, 1.0);
}