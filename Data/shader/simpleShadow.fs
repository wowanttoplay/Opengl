#version 330 core
// out vec4 fragColor;

// float LinearizeDepth(float depth) {
//   float z = depth * 2.0 - 1.0;  // Back to NDC
//   return (2.0 * 0.1 * 10.0) / (10.0 + 0.1 - z * (10.0 - 0.1));
// }

void main() {
  //   float depth = gl_FragCoord.z;
  //   fragColor = vec4(vec3(LinearizeDepth(depth) / 10.0), 0.1);
  // gl_FragDepth = 0.3;
}
