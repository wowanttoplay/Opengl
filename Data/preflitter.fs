// IBL镜反射预滤波环境贴图
#version 330 core
out vec4 FragColor;
in vec3 localPosition;

uniform samplerCube cubeMap0;
uniform float roughness;  // 不同粗糙度的不同处理

const float PI = 3.1415926;

float DistributionGGX(vec3 N, vec3 H, float roughness);  //
float RadicalInverse_VdC(uint bits);                     //一个生成均匀随机数的函数
vec2 Hammersley(uint i, uint N);  // 一个身成二维均匀随机数的函数，更均匀，但是受限于N
vec3 ImportanceSampleGGX(vec2 Xi, vec3 N, float roughness);  // 重要性采样

void main() {
  vec3 N = normalize(localPosition);
  vec3 R = N;
  vec3 V = R;

  const uint kSamplerCount = 1024u;
  vec3 prefilter_color = vec3(0.0);
  float total_weight = 0.0;  //权重和，用于求积分

  for (uint i = 0u; i < kSamplerCount; ++i) {
    vec2 Xi = Hammersley(i, kSamplerCount);
    vec3 H = ImportanceSampleGGX(Xi, N, roughness);
    vec3 L = normalize(2.0 * dot(V, H) * H - V);  //通过V和H反推出L

    float NdotL = max(dot(N, L), 0.0);
    if (NdotL > 0.0) {
      prefilter_color += texture(cubeMap0, L).rgb * NdotL;
      total_weight += NdotL;
    }
  }

  prefilter_color = prefilter_color / total_weight;
  FragColor = vec4(prefilter_color, 1.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
  float a = roughness * roughness;
  float a2 = a * a;
  float NdotH = max(dot(N, H), 0.0);
  float NdotH2 = NdotH * NdotH;

  float nom = a2;
  float denom = (NdotH2 * (a2 - 1.0) + 1.0);
  denom = PI * denom * denom;

  return nom / denom;
}

float RadicalInverse_VdC(uint bits) {
  bits = (bits << 16u) | (bits >> 16u);
  bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
  bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
  bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
  bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
  return float(bits) * 2.3283064365386963e-10;  // / 0x100000000
}

vec2 Hammersley(uint i, uint N) { return vec2(float(i) / float(N), RadicalInverse_VdC(i)); }

vec3 ImportanceSampleGGX(vec2 Xi, vec3 N, float roughness) {
  float a = roughness * roughness;

  float phi = 2.0 * PI * Xi.x;
  float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a * a - 1.0) * Xi.y));
  float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

  // from spherical coordinates to cartesian coordinates - halfway vector
  vec3 H;
  H.x = cos(phi) * sinTheta;
  H.y = sin(phi) * sinTheta;
  H.z = cosTheta;

  // from tangent-space H vector to world-space sample vector
  vec3 up = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
  vec3 tangent = normalize(cross(up, N));
  vec3 bitangent = cross(N, tangent);

  vec3 sampleVec = tangent * H.x + bitangent * H.y + N * H.z;
  return normalize(sampleVec);
}
