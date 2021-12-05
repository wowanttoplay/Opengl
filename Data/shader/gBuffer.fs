#version 330 core
layout(location = 0) out vec4 fPosition;
layout(location = 1) out vec3 fNormal;
layout(location = 2) out vec4 fAlbedoColor;

uniform vec4 albedoColor;
uniform float specularIntensity;
uniform float nearPlane;
uniform float farPlane;

in VS_OUT {
  vec3 position;
  vec3 normal;
  vec2 uv;
}
fs_in;

float LinearizeDepth(float depth) {
  float z = depth * 2.0 - 1.0;  // 回到NDC
  return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

void main() {
  fPosition.rgb = fs_in.position;
  fPosition.a = LinearizeDepth(gl_FragCoord.z);
  fNormal = normalize(fs_in.normal);
  fAlbedoColor = albedoColor;
  fAlbedoColor.a = specularIntensity;
}