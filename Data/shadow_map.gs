layout(triangles) in;
layout(triangles, max_vertices = 18) out;

uniform mat4 shadowMatrix[6];
out vec4 frag_pos;

void main() {
  for (int face = 0; face < 6; ++face) {
    gl_Layer = face;
    for (int i = 0; i < 3; ++i) {
      frag_pos = gl_in[i].gl_Position;
      gl_Position = shadowMatrix[face] * frag_pos;
      EmitVertex();
    }
    EndPrimitive();
  }
}