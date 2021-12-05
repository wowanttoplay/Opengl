// 直接绘制纹理
#version 330 core
uniform sampler2D texUnit;
uniform float farPlane;
uniform float nearPlane;
uniform int type;  // 0 :shadowMap, 1: rgb texture 2: rgba
in vec2 vTexCoords;

out vec4 fragColor;

float LinearizeDepth(float depth) {
  float z = depth * 2.0 - 1.0;  // Back to NDC
  return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

void main() {
  vec4 data = texture(texUnit, vTexCoords);
  if (type == 0) {
    float depth = data.r;
    fragColor = vec4(vec3(LinearizeDepth(depth) / farPlane), 1.0);
  } else if (type == 1) {
    fragColor = vec4(data.rgb, 1.0);
  } else if (type == 2) {
    fragColor = data;
  } else if (type == 3) {
    fragColor = vec4(vec3(data.r), 1.0);
  } else if (type == 4) {
    fragColor = vec4(vec3(data.g), 1.0);
  } else if (type == 5) {
    fragColor = vec4(vec3(data.b), 1.0);
  } else if (type == 6) {
    fragColor = vec4(vec3(data.a), 1.0);
  } else {
    fragColor = data;
  }
}