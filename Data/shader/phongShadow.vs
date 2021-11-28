// 带有阴影的phong光照模型渲染，按照距离的平方做能量衰减
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightMVP;

out vec4 positionFromLight;

out VS_OUT {
  vec2 texCoords;
  vec3 fragPos;
  vec3 normal;
}
vs_out;

void main() {
  vs_out.fragPos = vec3(model * vec4(aPos, 1.0));
  vs_out.texCoords = aTexCoords;
  vs_out.normal = mat3(transpose(inverse(model))) * aNormal;

  gl_Position = projection * view * model * vec4(aPos, 1.0);

  positionFromLight = lightMVP * vec4(aPos, 1.0);
}