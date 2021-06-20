// 已经废弃
#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

uniform mat4 mirrorMatrices[6];

in VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
}
gs_in[];

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main() {
  for (int face = 0; face < 6; ++face) {
    // if (face != 5) continue;
    gl_Layer = face;
    for (int i = 0; i < 3; ++i) {
      FragPos = gs_in[i].FragPos;
      Normal = gs_in[i].Normal;
      TexCoords = gs_in[i].TexCoords;
      gl_Position = mirrorMatrices[face] * gl_in[i].gl_Position;
      EmitVertex();
    }
    EndPrimitive();
  }
}