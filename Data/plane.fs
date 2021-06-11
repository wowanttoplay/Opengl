#version 330 core
in vec2 texCoords;
uniform vec4 mixColor;
uniform sampler2D texture0;
out vec4 fragcolor;

void main() { fragcolor = texture(texture0, texCoords) * mixColor; }