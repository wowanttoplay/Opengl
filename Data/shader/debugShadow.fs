// 直接绘制纹理
#version 330 core
uniform sampler2D texUnit;
uniform float farPlane;
uniform float nearPlane;
in vec2 vTexCoords;

out vec4 fragColor;

float LinearizeDepth(float depth) {
  float z = depth * 2.0 - 1.0;  // Back to NDC
  return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

void main() {
  float depth = texture(texUnit, vTexCoords).r;
  fragColor = vec4(vec3(LinearizeDepth(depth) / farPlane), nearPlane);
}