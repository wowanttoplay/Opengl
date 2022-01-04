#version 330 core
struct BaseLight {
  vec3 position;
  vec3 color;
  float radius;
  float nearPlane;
  float farPlane;
};

in vec2 vTexCoords;
out vec4 fragColor;

uniform sampler2D fPosition;
uniform sampler2D fNormal;
uniform sampler2D fAlberdo;
uniform sampler2D fAoMap;
uniform sampler2D shadowMap;

uniform mat4 view;
uniform mat4 lightVP;

uniform BaseLight light;
#define EPS 0.001
#define NUM_SAMPLES 20  // 采样个数
#define NUM_RINGS 10    // 柏松采样的圈数,数据代表采样共形成多少圈
#define PI 3.141592653589793
#define PI2 6.283185307179586

vec2 poissonDisk[NUM_SAMPLES];

float rand_1to1(float x) {
  // 0~1的随机数
  return fract(sin(x) * 100000.0);
}

float rand_2to1(vec2 uv) {
  const float a = 12.9898, b = 78.233, c = 43758.5453;
  float dt = dot(uv, vec2(a, b)), sn = mod(dt, PI);
  return fract(sin(sn) * c);
}

float LinearizeDepth(float depth) {
  float nearPlane = light.nearPlane;
  float farPlane = light.farPlane;
  float z = depth * 2.0 - 1.0;  // Back to NDC
  return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

void poissonDiskSamples(const in vec2 randSeed) {
  float ANGLE_STEP = PI2 * float(NUM_RINGS) / float(NUM_SAMPLES);
  float INV_NUM_SAMPLES = 1.0 / float(NUM_SAMPLES);

  float angle = rand_2to1(randSeed) * PI2;
  float radius = INV_NUM_SAMPLES;
  float radiusStep = radius;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    poissonDisk[i] = vec2(cos(angle), sin(angle)) * pow(radius, 0.75);
    radius += radiusStep;
    angle += ANGLE_STEP;
  }
}

void uniformDiskSamples(const in vec2 randomSeed) {
  float randNum = rand_2to1(randomSeed);
  float sampleX = rand_1to1(randNum);
  float sampleY = rand_1to1(sampleX);

  float angle = sampleX * PI2;
  float radius = sqrt(sampleY);

  for (int i = 0; i < NUM_SAMPLES; i++) {
    poissonDisk[i] = vec2(radius * cos(angle), radius * sin(angle));

    sampleX = rand_1to1(sampleY);
    sampleY = rand_1to1(sampleX);

    angle = sampleX * PI2;
    radius = sqrt(sampleY);
  }
}

// 获取遮挡物的深度
float getBlockDepth(sampler2D shadowMap, vec4 shadowCoord) {
  // 获取遮挡物的深度的步长应该大一点
  poissonDiskSamples(shadowCoord.xy);
  vec2 size = vec2(textureSize(shadowMap, 0));
  vec2 texelSize = vec2(1.0) / size;  // 纹理单纹素纹理坐标
  float filterStride = 10.0;          // 步长
  vec2 filterRange = filterStride * texelSize;

  int blockNum = 0;
  float blockDepth = 0.0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    float depth = texture(shadowMap, poissonDisk[i] * filterRange + shadowCoord.xy).r;
    if (depth < EPS) depth = 1.0;
    // 检测是否为遮挡物，不是遮挡物的不统计
    if (depth < shadowCoord.z && shadowCoord.z < 1.0 && depth < 1.0) {
      blockDepth += depth;
      blockNum += 1;
    }
  }
  if (blockNum == 0) return 1.0;  // 避免除0
  return float(blockDepth) / float(blockNum);
}

float PCSS(sampler2D shadowMap, vec4 shadowCoord) {
  // 获取遮挡物的平均深度
  float blockDepth = getBlockDepth(shadowMap, shadowCoord);
  // 根据遮挡物的深度，计算过滤的步长
  vec2 size = vec2(textureSize(shadowMap, 0));
  vec2 texelSize = vec2(1.0) / size;            // 纹理单纹素纹理坐标
  float filterStride = 1.0;                     // 步长
  vec2 filterRange = filterStride * texelSize;  // 基础的过滤偏移
  float zReceiver = min(shadowCoord.z, 1.0);

  zReceiver = LinearizeDepth(shadowCoord.z) / light.farPlane;

  blockDepth = LinearizeDepth(blockDepth) / light.farPlane;
  if (blockDepth < EPS) return 1.0;

  float k = (zReceiver - blockDepth) / blockDepth;

  filterRange = max(light.radius * 20 * filterRange * k, filterRange);  // 让效果更明显
  // 计算遮挡比率，返回可见性
  const float bias = 0.0001;
  int visibilityNum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    float depth = texture(shadowMap, poissonDisk[i] * filterRange + shadowCoord.xy).r;
    if (depth + bias > shadowCoord.z || depth < EPS || shadowCoord.z >= 1.0) {
      visibilityNum += 1;
    }
  }

  return float(visibilityNum) / float(NUM_SAMPLES);
}

float PCF(sampler2D shadowMap, vec4 shadowCoord) {
  poissonDiskSamples(shadowCoord.xy);
  vec2 size = vec2(textureSize(shadowMap, 0));
  vec2 texelSize = vec2(1.0) / size;  // 纹理单纹素纹理坐标
  float filterStride = 3.0;           // 步长
  vec2 filterRange = filterStride * texelSize;
  int visibilityNum = 0;
  float bias = 0.0001;

  for (int i = 0; i < NUM_SAMPLES; ++i) {
    float depth = texture(shadowMap, poissonDisk[i] * filterRange + shadowCoord.xy).r;
    if (depth + bias > shadowCoord.z || depth < EPS || shadowCoord.z > 1.0) {
      visibilityNum += 1;
    }
  }
  float shadow = float(visibilityNum) / float(NUM_SAMPLES);
  return shadow;
}

float directUseShadowMap(sampler2D shadowMap, vec4 shadowCoord) {
  float depth = texture(shadowMap, shadowCoord.xy).r;
  const float bias = 0.00010;
  if (depth + bias > shadowCoord.z || depth < EPS || shadowCoord.z > 1.0) {
    return 1.0;
  }

  return 0.0;
}

float calculateVisibility() {
  float visibility = 0.0;
  vec4 positionFromLight = lightVP * inverse(view) * vec4(texture(fPosition, vTexCoords).xyz, 1.0);
  vec3 shadowCoord = positionFromLight.xyz / positionFromLight.w;
  shadowCoord = (shadowCoord + vec3(1.0)) * 0.5;
  //   visibility = directUseShadowMap(shadowMap, vec4(shadowCoord, 1.0));
  //   visibility = PCF(shadowMap, vec4(shadowCoord, 1.0));
  visibility = PCSS(shadowMap, vec4(shadowCoord, 1.0));
  return visibility;
}

vec3 blinnPhong(float visibility, float ao) {
  vec4 albedoColor = texture(fAlberdo, vTexCoords);
  float specularIntensity = albedoColor.w;
  vec3 color = albedoColor.rgb;
  color = pow(color, vec3(2.2));

  vec4 viewPosition = texture(fPosition, vTexCoords);
  vec3 viewNormal = texture(fNormal, vTexCoords).rgb;

  // ambient
  vec3 ambient = 0.3 * color;

  // diffuse
  vec3 lightDir = normalize(light.position - viewPosition.xyz);
  vec3 normal = normalize(viewNormal);
  float diff = max(dot(lightDir, normal), 0.0);

  vec3 light_atten_coff = light.color / pow(length(light.position - viewPosition.xyz), 2.0);
  vec3 diffuse = diff * light_atten_coff * color;

  // specular
  vec3 viewDir = normalize(-viewPosition.xyz);
  vec3 halfDir = normalize(viewDir + lightDir);
  float spec = pow(max(dot(normal, halfDir), 0.0), specularIntensity);
  vec3 specular = spec * light_atten_coff * color;

  vec3 radiance = (ambient * ao + (diffuse + specular) * visibility);
  vec3 phongColor = pow(radiance, vec3(1.0 / 2.2));
  return phongColor;
}

void main() {
  float visibility = calculateVisibility();
  float ao = texture(fAoMap, vTexCoords).r;
  vec3 color = blinnPhong(visibility, ao);

  fragColor = vec4(color, 1.0);
}