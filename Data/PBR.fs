#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D albedoTexture;

uniform float metallic;   // 描述其金属性
uniform float roughness;  // 粗糙度
uniform float ao;         // ao值

uniform vec3 cameraPosition;  // 相机位置
uniform vec3 lightPosition;  //光源位置
uniform vec3 light_color;

uniform samplerCube depthMap;  // 深度贴图
uniform float farPlane;        // 计算深度贴图时归一化用的远平面

const float PI = 3.1415926;
vec3 gridSamplingDisk[20] =
    vec3[](vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1), vec3(1, 1, -1),
           vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1), vec3(1, 1, 0), vec3(1, -1, 0),
           vec3(-1, -1, 0), vec3(-1, 1, 0), vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1),
           vec3(-1, 0, -1), vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1));

vec3 fresnelSchlick(float cosTheta, vec3 F0);
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
float ShadowCalculate(vec3 fragPosition);

void main() {
  vec3 albedo = texture(albedoTexture, TexCoords).rgb;
  
  vec3 L0 = vec3(0.0);

  vec3 N = normalize(Normal);
  vec3 V = normalize(cameraPosition - FragPos);
  //...
  vec3 L = normalize(lightPosition - FragPos);
  vec3 H = normalize(V + L);

  float dis = length(FragPos - lightPosition);
  float attenuation = 1.0 / (dis * dis);  //从物理上来讲，平方倒数的衰减更准确
  vec3 radiance = light_color * attenuation;

  // 计算BDRF中的反射部分
  /*首先计算ks*/
  vec3 F0 = vec3(0.04);
  F0 = mix(F0, albedo, metallic);  //对金属的处理，金属的反射会变色
  vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

  /*计算NDF分布*/
  float NDF = DistributionGGX(N, H, roughness);

  /*计算几何遮蔽*/
  float G = GeometrySmith(N, V, L, roughness);

  vec3 numerator = NDF * G * F;

  float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
  vec3 specular = numerator / max(denominator, 0.0001);  // 反射部分

  vec3 ks = F;
  vec3 kd = vec3(1.0) - ks;
  kd *= (1.0 - metallic);  // 因为金属不会有折射

  float NdotL = max(dot(N, L), 0.0);
  L0 += (kd * albedo / PI + specular) * radiance * NdotL;

 vec3 color = vec3(0.0);
  //加上环境光照
  vec3 ambient = vec3(0.03) * albedo * ao;
  color += ambient;

  // 计算阴影
  float shadow = ShadowCalculate(FragPos);

  color += L0 * (1.0 - shadow);

  FragColor = vec4(color, 1.0);
}

// 菲尼尔方程
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
  return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

// 正态分布函数
float DistributionGGX(vec3 N, vec3 H, float roughness) {
  float a = roughness * roughness;
  float a2 = a * a;
  float NdotH = max(dot(N, H), 0.0);
  float NdotH2 = NdotH * NdotH;

  float numerator = a2;
  float denominator = (NdotH2 * (a2 - 1.0) + 1.0);
  denominator = PI * denominator * denominator;
  return numerator / max(denominator, 0.00001);
}

// 几何函数
float GeometrySchlickGGX(float NdotV, float roughness) {
  // 直接光照的k值计算
  float r = roughness + 1.0;
  float k = (r * r) / 8.0;

  float numerator = NdotV;
  float denominator = numerator * (1 - k) + k;
  return numerator / denominator;
}

// 要同时考虑几何遮蔽和几何阴影，视线和入射光线都有可能被遮蔽
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
  float NdotV = max(dot(N, V), 0.0);
  float NdotL = max(dot(N, L), 0.0);
  float ggxV = GeometrySchlickGGX(NdotV, roughness);
  float ggxL = GeometrySchlickGGX(NdotL, roughness);
  return ggxL * ggxV;
}

// 深度使用的是之前自己定义的深度，表示距离光源的距离
float ShadowCalculate(vec3 fragPosition) {
  vec3 light_to_frag = fragPosition - lightPosition;
  float current_depth = length(light_to_frag);  // 当前的片段的深度
  float shadow = 0.0;
  float bias = 0.15;
  int samples = 20;
  float camera_distance = length(cameraPosition - fragPosition);
  float diskRadius = (1.0 + (camera_distance / farPlane)) / 25.0;

  for (int i = 0; i < samples; ++i) {
    float closestDepth = texture(depthMap, light_to_frag + gridSamplingDisk[i] * diskRadius).r;
    closestDepth *= farPlane;  // undo mapping [0;1]
    if (current_depth - bias > closestDepth) shadow += 1.0;
  }
  shadow /= float(samples);
  return shadow;
}