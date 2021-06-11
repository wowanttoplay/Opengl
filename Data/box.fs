#version 330 core
in vec2 texCoords;
uniform sampler2D texture0;

out vec4 fragcolor;

void main() {
  vec4 color = vec4(0.0);
  color = texture(texture0, texCoords);
  fragcolor = color;
}