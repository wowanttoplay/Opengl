#version 330 core
out vec4 FragColor;

in vec3 localPosition;
uniform samplerCube skyMap;

void main() {
  vec3 skyColor = texture(skyMap, localPosition).rgb;
  FragColor = vec4(skyColor, 1.0);
}