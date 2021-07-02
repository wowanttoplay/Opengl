#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 view;
uniform mat4 projection;


out vec3 localPosition;

void main() {
  localPosition = aPosition;
  mat4 rotView = mat4(mat3(view));  //去除移动
  vec4 clipPos = projection * rotView * vec4(aPosition, 1.0);

  gl_Position = clipPos.xyww;  //保证深度为1
}