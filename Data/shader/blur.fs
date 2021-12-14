#version 330 core
in vec2 vTexCoords;
out vec4 fragColor;

uniform sampler2D blurTarget;
uniform int blurType;

vec4 gaussianBlur() {
  vec2 texelSize = 1.0 / vec2(textureSize(blurTarget, 0));
  vec4 result = vec4(0.0);
  for (int x = -2; x < 2; ++x) {
    for (int y = -2; y < 2; ++y) {
      vec2 offset = vec2(float(x), float(y)) * texelSize;
      result += texture(blurTarget, vTexCoords + offset);
    }
  }
  return result / (4.0 * 4.0);
}

vec4 BilateralBlur() {
  // todo
  return vec4(1.0);
}

void main() {
  vec4 color = vec4(0.0);
  if (blurType == 0) {
    color = gaussianBlur();
  } else if (blurType == 1) {
    color = BilateralBlur();
  }

  fragColor = color;
}