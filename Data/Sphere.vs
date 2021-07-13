#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 Model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT {
  vec3 Normal;
}
vs_out;

void main() {
  gl_Position = projection * view * Model * vec4(aPosition, 1.0);
  vs_out.Normal = transpose(inverse(mat3(Model))) * aNormal;
}
