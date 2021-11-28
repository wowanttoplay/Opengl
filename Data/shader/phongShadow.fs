#version 330 core

struct BaseLight {
  vec3 position;
  vec3 color;
};

uniform sampler2D shadowMap;
uniform vec4 objectColor;
uniform float specularIntensity;
uniform vec3 cameraPos;
uniform BaseLight light;

out vec4 fragColor;

in VS_OUT {
  vec2 texCoords;
  vec3 fragPos;
  vec3 normal;
}
fs_in;
in vec4 positionFromLight;

float directUseShadowMap(sampler2D shadowMap, vec4 shadowCoord) {
  float depth = texture(shadowMap, shadowCoord.xy).r;
  const float bias = 0.01;
  if (depth + bias > shadowCoord.z) {
    return 1.0;
  }

  return 0.0;
}

vec3 blinnPhong() {
  vec3 color = objectColor.rgb;
  color = pow(color, vec3(2.2));

  vec3 ambient = 0.05 * color;

  vec3 lightDir = normalize(light.position - fs_in.fragPos);
  vec3 normal = normalize(fs_in.normal);
  float diff = max(dot(lightDir, normal), 0.0);

  vec3 light_atten_coff = light.color / pow(length(light.position - fs_in.fragPos), 2.0);
  vec3 diffuse = diff * light_atten_coff * color;

  vec3 viewDir = normalize(cameraPos - fs_in.fragPos);
  vec3 halfDir = normalize(viewDir + lightDir);
  float spec = pow(max(dot(normal, halfDir), 0.0), specularIntensity);
  vec3 specular = spec * light_atten_coff * color;

  vec3 radiance = (ambient + diffuse + specular);
  vec3 phongColor = pow(radiance, vec3(1.0 / 2.2));
  return phongColor;
}

float calculateVisibility() {
  // 计算可见性
  float visibility = 0.0;
  vec3 shadowCoord = positionFromLight.xyz / positionFromLight.w;
  shadowCoord = (shadowCoord + vec3(1.0)) * 0.5;
  visibility = directUseShadowMap(shadowMap, vec4(shadowCoord, 1.0));
  return visibility;
}

void main() {
  float visibility = calculateVisibility();
  vec3 phongColor = blinnPhong();
  fragColor = vec4(phongColor * visibility, 1.0);
}
