#version 330 core
in vec2 texCoords;
uniform sampler2D texture1;
out vec4 fragcolor;

uniform float time;

void main() 
{ 
    fragcolor = texture(texture1, texCoords); 
}