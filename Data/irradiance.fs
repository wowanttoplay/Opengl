#version 330 core

out vec4 FragColor;
in vec3 localPosition;  // 为该点半球的normal
uniform samplerCube curbMap0;

const float PI = 3.1415926;

void main() {
  vec3 N = normalize(localPosition);
  vec3 irradiance = vec3(0.0);
  vec3 up = vec3(0.0, 1.0, 0.0);
  vec3 right = normalize(cross(up, N));
  up = normalize(cross(N, right));

  float sampleDelta = 0.025;  //离散积分的步长
  float number = 0.0;         //计算积分次数，最后去平均

  for (float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta) {
    for (float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta) {
      // 在半球空间中的位置
      vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
      // 转化到世界空间中
      vec3 sampleWorld = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N;
      // 取样
      irradiance = irradiance + texture(curbMap0, sampleWorld).rgb * cos(theta) * sin(theta);
      ++number;
    }
  }

  irradiance = PI * irradiance * (1.0 / float(number));

  FragColor = vec4(irradiance, 1.0);
}
