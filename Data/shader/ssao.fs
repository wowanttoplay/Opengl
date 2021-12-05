#version 330 core
#define SAMPLE_NUM 64

out float fragColor;

in vec2 vTexCoords;

uniform sampler2D fPosition;
uniform sampler2D fNormal;
uniform sampler2D fNoise;
uniform mat4 projection;

uniform vec3 samples[SAMPLE_NUM];
uniform float screenWidth;
uniform float screenHeight;

const float radius = 0.5;  // 采样球半径
const float bias = 0.001;  // 深度比较的容差

void main() {
  vec3 fragPos = texture(fPosition, vTexCoords).rgb;
  vec3 normal = normalize(texture(fNormal, vTexCoords).rgb);
  vec2 noiseSize = textureSize(fNoise, 0);
  vec2 noiseScale = vec2(screenWidth / noiseSize.x, screenHeight / noiseSize.y);
  vec3 noise = normalize(texture(fNoise, vTexCoords * noiseScale).rgb);

  vec3 tangent = normalize(noise - normal * dot(noise, normal));
  vec3 bitangent = cross(normal, tangent);
  mat3 TBN = mat3(tangent, bitangent, normal);

  float occlusion = 0.0;
  for (int i = 0; i < SAMPLE_NUM; i++) {
    vec3 samplePos = TBN * samples[i];
    samplePos = fragPos + samplePos * radius;
    vec4 offsetPos = vec4(samplePos, 1.0);
    offsetPos *= projection;
    offsetPos = offsetPos / offsetPos.w;
    offsetPos.xyz = offsetPos.xyz * 0.5 + 0.5;

    float sampleDepth = -texture(fPosition, samplePos.xy).z;  // 纹理中该位置存储的z值，向屏幕内是z负轴，需要反一下

    float rangeCheck = smoothstep(0.0, 1.0, radius / abs(sampleDepth - samplePos.z));
    occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0) * rangeCheck;
  }
  occlusion = 1.0 - occlusion / float(SAMPLE_NUM);  // 越小，遮挡越多
  fragColor = occlusion;
}