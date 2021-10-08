#version 330 core

struct Light {
  vec3 position;  //位置
  vec3 color;     //光源颜色
  // 光照衰减参数
  float constant;
  float linear;
  float quadratic;
};

in VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
}
fs_in;

uniform sampler2D texture0;         // 纹理贴图
uniform samplerCube depth_texture;  // 深度贴图

uniform int shadow_type = 0;  // 0 :normal shadow map 1: pcf 2: pcss

uniform float
    far_plane;  // 远平面位置，因为我们在阴影texture中的深度值是用far_plane算的，显示阴影的时候也需要far_plane来做对比
uniform vec3 cameraPosition;  // 相机位置
out vec4 fragcolor;           // 输出的颜色
uniform Light light;          // 光照相关参数

float NomralShadowCalculate(vec3 fragPosition);

float PCLShadowCalculate(vec3 fragPosition);

float PCSSShadowCalculate(vec3 fragPosition);

void main() {
  vec3 color = vec3(texture(texture0, fs_in.TexCoords));  // 地板本来的颜色
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
  // shadow calculate
  float shadow = 0.0;
  if (shadow_type == 0) {
    shadow = NomralShadowCalculate(fs_in.FragPos);
  } else if (shadow_type == 1) {
    shadow = PCLShadowCalculate(fs_in.FragPos);
  } else {
    shadow = PCSSShadowCalculate(fs_in.FragPos);
  }

  // 光照衰减
  float distance = length(light.position - fs_in.FragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
  // frag color,考虑光衰减和阴影
  fragcolor = vec4(vec3(ambient + (diffuse + specular) * (1 - shadow)) * attenuation, 1.0);
}

vec3 gridSamplingDisk[20] = vec3[](vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1), vec3(1, 1, -1),
                                   vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1), vec3(1, 1, 0), vec3(1, -1, 0),
                                   vec3(-1, -1, 0), vec3(-1, 1, 0), vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1),
                                   vec3(-1, 0, -1), vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1));

// 深度使用的是之前自己定义的深度，表示距离光源的距离
float PCLShadowCalculate(vec3 fragPosition) {
  vec3 light_to_frag = fragPosition - light.position;
  // float close_depth = texture(depth_texture, light_to_frag).r;
  // close_depth *= far_plane;  //    当初的深度值就是length/far_plane，所以这里要还原
  float current_depth = length(light_to_frag);  // 当前的片段的深度
  float shadow = 0.0;
  float bias = 0.15;
  int samples = 20;
  float camera_distance = length(cameraPosition - fragPosition);
  float diskRadius = (1.0 + (camera_distance / far_plane)) / 25.0;

  for (int i = 0; i < samples; ++i) {
    float closestDepth = texture(depth_texture, light_to_frag + gridSamplingDisk[i] * diskRadius).r;
    closestDepth *= far_plane;  // undo mapping [0;1]
    if (current_depth - bias > closestDepth) shadow += 1.0;
  }
  shadow /= float(samples);
  return shadow;
}

float NomralShadowCalculate(vec3 fragPosition) { 
  vec3 light_to_frag = fragPosition - light.position;
  float current_depth = length(light_to_frag);
  float bias = 0.15;

  // 直接比较，会产生硬阴影
  float closestDepth = texture(depth_texture, light_to_frag).r * far_plane;
  if (current_depth - bias > closestDepth) return 1.0;
  return 0.0;
 }

float PCSSShadowCalculate(vec3 fragPosition) { 
  return 0.0;
}