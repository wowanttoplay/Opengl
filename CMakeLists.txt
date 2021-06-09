cmake_minimum_required(VERSION 3.17)
project(Opengl)

set(CMAKE_CXX_STANDARD 20)

# 添加头文件
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL/)
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include/GLFW)
include_directories(${GLEW_H} ${GLFW_H})
# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

add_executable(Opengl main.cpp window/Window.cc window/Window.h Data/vertex_data.h Thread/Task.cc Thread/Task.h Thread/ThreadPool.cc Thread/ThreadPool.h shader/shader_data.h shader/ShaderFactory.cc shader/ShaderFactory.h Tool/PrintTool.cc Tool/PrintTool.h Log/LogUtil.cc Log/LogUtil.h)

if (APPLE)
    target_link_libraries(Opengl "-framework OpenGL")
    target_link_libraries(Opengl "-framework GLUT")
endif()