#version 330 core
uniform vec4 mixColor;
uniform vec3 cameraPosition;  // 相机位置

struct Light {
  vec3 position;  //位置
  vec3 color;     //光源颜色
  // 光照衰减参数
  float constant;
  float linear;
  float quadratic;
};

uniform sampler2D texture0;
out vec4 fragcolor;

in VS_OUT {
  vec2 texCoords;
  vec3 FragPos;
  vec3 Normal;
}
fs_in;

uniform Light light;

void main() {
  vec3 color = vec3(texture(texture0, fs_in.texCoords) * mixColor);  // 地板本来的颜色
  // vector(from light、camera to fragment)
  vec3 lightDir = normalize(vec3(light.position - fs_in.FragPos));
  vec3 cameraDir = normalize(vec3(cameraPosition - fs_in.FragPos));
  vec3 normal = normalize(fs_in.Normal);
  // ambient
  vec3 ambient = 0.05 * color * light.color;
  // diffuse
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = diff * color * light.color;
  // blinn specular
  vec3 reflectDir = reflect(-lightDir, fs_in.Normal);
  vec3 halfDir = normalize(reflectDir + cameraDir);
  float spec = pow(max(dot(halfDir, fs_in.Normal), 0.0), 32.0);
  vec3 specular = spec * color * light.color;
  // 光照衰减
  float distance = length(light.position - fs_in.FragPos);
  float attenuation =
      1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
  // frag color
  fragcolor = vec4(vec3(ambient + diffuse + specular) * attenuation, 1.0);
}