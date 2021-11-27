cmake_minimum_required(VERSION 3.17)
project(Opengl)

set(CMAKE_CXX_STANDARD 20)

find_package(glog 0.6.0 REQUIRED)

# 添加头文件
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL/)
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include/GLFW)
set(GLM_H /usr/local/Cellar/glm)
#set(ASSIMP_H /usr/local/Cellar/assimp/include/assimp)
include_directories(${GLEW_H} ${GLFW_H} ${GLM_H} )
# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.dylib)
#set(ASSIMP_LINK /usr/local/Cellar/assimp/bin/libassimp.5.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} )

add_executable(Opengl main.cpp window/Window.cc window/Window.h Shader.cc Shader.h Texture2D.cc Texture2D.h ResourceManager.cc ResourceManager.h RenderObject/Plane.cc RenderObject/Plane.h Scene.cc Scene.h RenderObject/Box.cc RenderObject/Box.h RenderObject/Sphere.cc RenderObject/Sphere.h RenderPass/HDRProcess.h RenderPass/ShadowProcess.cc RenderPass/ShadowProcess.h Camera.cc Camera.h RenderObject/BaseObject.cc RenderObject/BaseObject.h RenderObject/Light/BaseLight.cc RenderObject/Light/BaseLight.h RenderObject/Light/PointLight.cc RenderObject/Light/PointLight.h)
target_link_libraries(Opengl glog::glog)

if (APPLE)
    target_link_libraries(Opengl "-framework OpenGL")
    target_link_libraries(Opengl "-framework GLUT")
endif()