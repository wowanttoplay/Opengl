#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D hdrTexture;
uniform sampler2D blurTexture;
uniform float exposure;
uniform float gamma;
uniform bool b_bright;  //控制是否进行亮色绘制
uniform bool b_blur;    // 是否泛光

void main() {
  vec3 hdrColor = texture(hdrTexture, TexCoords).rgb;
  // 是否单纯的输出亮色
  if (b_bright) {
    float brightness = dot(hdrColor, vec3(0.2126, 0.7152, 0.0722));
    if (brightness > 1.0) {
      FragColor = vec4(hdrColor, 1.0);
    } else {
      FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    return;
  }
  // 曝光
  if (b_blur) {
    vec3 blurColor = texture(blurTexture, TexCoords).rgb;
    hdrColor += blurColor;
  }
  vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
  result = pow(result, vec3(1.0 / gamma));
  FragColor = vec4(result, 1.0);
}