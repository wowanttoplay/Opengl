#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D hdrTexture;
uniform bool b_dbr;
uniform float exposure;
uniform float gamma;

void main() {
  vec3 hdrColor = texture(hdrTexture, TexCoords).rgb;
  if (b_dbr) {
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
  } else {
    vec3 result = pow(hdrColor, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
  }
}