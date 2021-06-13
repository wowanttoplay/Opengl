#version 330 core

struct Light {
  vec3 position;  //位置
  vec3 color;     //光源颜色
  // 光照衰减参数
  float constant;
  float linear;
  float quadratic;
};

in VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
}
fs_in;

uniform sampler2D texture0;         // 纹理贴图
uniform samplerCube depth_texture;  // 深度贴图

uniform float far_plane;  // 远平面位置，因为我们在阴影texture中的深度值是用far_plane算的，显示阴影的时候也需要far_plane来做对比
uniform vec3 cameraPosition;  // 相机位置
out vec4 fragcolor;           // 输出的颜色
uniform Light light;          // 光照相关参数

float ShadowCalculate(vec3 fraPosition);

void main() {
  vec3 color = vec3(texture(texture0, fs_in.TexCoords));  // 地板本来的颜色
  // vector(from light、camera to fragment)
  vec3 lightDir = normalize(vec3(light.position - fs_in.FragPos));
  vec3 cameraDir = normalize(vec3(cameraPosition - fs_in.FragPos));
  vec3 normal = normalize(fs_in.Normal);
  // ambient
  vec3 ambient = 0.05 * color * light.color;
  // diffuse
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse = diff * color * light.color;
  // blinn specular
  vec3 reflectDir = reflect(-lightDir, fs_in.Normal);
  vec3 halfDir = normalize(reflectDir + cameraDir);
  float spec = pow(max(dot(halfDir, fs_in.Normal), 0.0), 32.0);
  vec3 specular = spec * color * light.color;
  // shadow calculate
  float shadow = ShadowCalculate(fs_in.FragPos);
  // 光照衰减
  float distance = length(light.position - fs_in.FragPos);
  float attenuation =
      1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
  // frag color,考虑光衰减和阴影
  fragcolor = vec4(vec3(ambient + (diffuse + specular) * (1 - shadow)) * attenuation, 1.0);

  

  // test
  //  vec3 light_to_frag = fs_in.FragPos - light.position;
  // float close_depth = texture(depth_texture, light_to_frag).r;
  // // close_depth *= far_plane;  //    当初的深度值就是length/far_plane，所以这里要还原
  // // close_depth *= 3;
  // fragcolor = vec4(vec3(close_depth), 1.0);
}

// 深度使用的是之前自己定义的深度，表示距离光源的距离
float ShadowCalculate(vec3 fraPosition) {
  vec3 light_to_frag = fraPosition - light.position;
  float close_depth = texture(depth_texture, light_to_frag).r;
  close_depth *= far_plane;  //    当初的深度值就是length/far_plane，所以这里要还原
  float current_depth = length(light_to_frag);  // 当前的片段的深度

  // fragcolor = vec4(vec3(close_depth/far_plane), 1.0);

  const float bias = 0.05;  //阴影偏移
  float shadow = current_depth - bias > close_depth ? 1.0 : 0.0;
  return shadow;
}