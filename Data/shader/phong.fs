#version 330 core

struct BaseLight {
  vec3 position;
  vec3 color;
};

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

void main() {
  vec3 phongColor = blinnPhong();
  fragColor = vec4(phongColor, 1.0);
}