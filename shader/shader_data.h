//
// Created by virgil on 2021/5/27.
//

#pragma once

namespace shaderSource {

    const char *base_vertex_shader = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "out vec4 color;"
                                     "void main()\n"
                                     "{\n"
                                     "   color = vec4(aPos, 1.0);\n"
                                     "   gl_Position = vec4(aPos, 1.0);\n"
                                     "}\0";

    const char *base_fragment_shader = "#version 330 core\n"
                                       "in vec4 color;"
                                       "out vec4 FragColor;\n"
                                       "uniform vec4 ourColor;"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = ourColor;\n"
                                       "}\n\0";


    const char *color_vertex_shader = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "out vec4 color;"
                                     "void main()\n"
                                     "{\n"
                                     "   color = vec4(aColor, 1.0);\n"
                                     "   gl_Position = vec4(aPos, 1.0);\n"
                                     "}\0";

    const char *color_fragment_shader = "#version 330 core\n"
                                       "in vec4 color;"
                                       "uniform float alpha;\n"
                                       "layout (location = 0) out vec4 out_color;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   out_color = vec4(color.rgb, alpha);\n"
                                       "}\n\0";

    const char* frame_vertex_shader = "#version 330 core\n"
                                      "layout (location = 0) in vec2 aPos;\n"
                                      "layout (location = 1) in vec2 aTexCoords;\n"
                                      "out vec2 TexCoords;\n"
                                      "void main() {\n"
                                      "  gl_Position = vec4(aPos, 0, 1.0);\n"
                                      "  TexCoords = aTexCoords;\n"
                                      "}\0";

    const char* frame_fragment_buffer_shader = "#version 330 core\n"
                                               "out vec4 FragColor;\n"
                                               "in vec2 TexCoords;\n"
                                               "uniform sampler2D screentexture;\n"
                                               "void main() {\n"
                                               "  FragColor = texture(screenTexture, TexCoords);\n"
                                               "}\0";

    const char* texture_vertex_shader = "#version 330 core;\n"
                                        "layout(location = 0) in vec2 aPos;\n"
                                        "layout(location = 1) in vec2 aTexCoords;\n"
                                        "out vec2 texCoords;\n"
                                        "void main() {\n"
                                        "  gl_Position = vec4(aPos, 0.0, 1.0);\n"
                                        "  TexCoords = aTexCoords;\n"
                                        "}\0";

    const char* texture_framgent_shader = "#version 330 core;\n"
                                          "in vec2 texCoords;\n"
                                          "uniform sampler2D texture_RGBA;\n"
                                          "out vec4 FragColor;\n"
                                          "void main() {\n"
                                          "  FragColor = texture(texture_RGBA, texCoords);\n"
                                          "}\0";

}



