# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/virgil/Opengl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/virgil/Opengl/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Opengl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Opengl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Opengl.dir/flags.make

CMakeFiles/Opengl.dir/main.cpp.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Opengl.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/main.cpp.o -c /Users/virgil/Opengl/main.cpp

CMakeFiles/Opengl.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/main.cpp > CMakeFiles/Opengl.dir/main.cpp.i

CMakeFiles/Opengl.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/main.cpp -o CMakeFiles/Opengl.dir/main.cpp.s

CMakeFiles/Opengl.dir/window/Window.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/window/Window.cc.o: ../window/Window.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Opengl.dir/window/Window.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/window/Window.cc.o -c /Users/virgil/Opengl/window/Window.cc

CMakeFiles/Opengl.dir/window/Window.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/window/Window.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/window/Window.cc > CMakeFiles/Opengl.dir/window/Window.cc.i

CMakeFiles/Opengl.dir/window/Window.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/window/Window.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/window/Window.cc -o CMakeFiles/Opengl.dir/window/Window.cc.s

CMakeFiles/Opengl.dir/Thread/Task.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Thread/Task.cc.o: ../Thread/Task.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Opengl.dir/Thread/Task.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Thread/Task.cc.o -c /Users/virgil/Opengl/Thread/Task.cc

CMakeFiles/Opengl.dir/Thread/Task.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Thread/Task.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Thread/Task.cc > CMakeFiles/Opengl.dir/Thread/Task.cc.i

CMakeFiles/Opengl.dir/Thread/Task.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Thread/Task.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Thread/Task.cc -o CMakeFiles/Opengl.dir/Thread/Task.cc.s

CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.o: ../Thread/ThreadPool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.o -c /Users/virgil/Opengl/Thread/ThreadPool.cc

CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Thread/ThreadPool.cc > CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.i

CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Thread/ThreadPool.cc -o CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.s

CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o: ../Tool/PrintTool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o -c /Users/virgil/Opengl/Tool/PrintTool.cc

CMakeFiles/Opengl.dir/Tool/PrintTool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Tool/PrintTool.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Tool/PrintTool.cc > CMakeFiles/Opengl.dir/Tool/PrintTool.cc.i

CMakeFiles/Opengl.dir/Tool/PrintTool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Tool/PrintTool.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Tool/PrintTool.cc -o CMakeFiles/Opengl.dir/Tool/PrintTool.cc.s

CMakeFiles/Opengl.dir/Log/LogUtil.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Log/LogUtil.cc.o: ../Log/LogUtil.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Opengl.dir/Log/LogUtil.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Log/LogUtil.cc.o -c /Users/virgil/Opengl/Log/LogUtil.cc

CMakeFiles/Opengl.dir/Log/LogUtil.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Log/LogUtil.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Log/LogUtil.cc > CMakeFiles/Opengl.dir/Log/LogUtil.cc.i

CMakeFiles/Opengl.dir/Log/LogUtil.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Log/LogUtil.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Log/LogUtil.cc -o CMakeFiles/Opengl.dir/Log/LogUtil.cc.s

CMakeFiles/Opengl.dir/Shader.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Shader.cc.o: ../Shader.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Opengl.dir/Shader.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Shader.cc.o -c /Users/virgil/Opengl/Shader.cc

CMakeFiles/Opengl.dir/Shader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Shader.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Shader.cc > CMakeFiles/Opengl.dir/Shader.cc.i

CMakeFiles/Opengl.dir/Shader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Shader.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Shader.cc -o CMakeFiles/Opengl.dir/Shader.cc.s

CMakeFiles/Opengl.dir/Texture2D.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Texture2D.cc.o: ../Texture2D.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Opengl.dir/Texture2D.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Texture2D.cc.o -c /Users/virgil/Opengl/Texture2D.cc

CMakeFiles/Opengl.dir/Texture2D.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Texture2D.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Texture2D.cc > CMakeFiles/Opengl.dir/Texture2D.cc.i

CMakeFiles/Opengl.dir/Texture2D.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Texture2D.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Texture2D.cc -o CMakeFiles/Opengl.dir/Texture2D.cc.s

CMakeFiles/Opengl.dir/ResourceManager.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/ResourceManager.cc.o: ../ResourceManager.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Opengl.dir/ResourceManager.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/ResourceManager.cc.o -c /Users/virgil/Opengl/ResourceManager.cc

CMakeFiles/Opengl.dir/ResourceManager.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/ResourceManager.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/ResourceManager.cc > CMakeFiles/Opengl.dir/ResourceManager.cc.i

CMakeFiles/Opengl.dir/ResourceManager.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/ResourceManager.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/ResourceManager.cc -o CMakeFiles/Opengl.dir/ResourceManager.cc.s

CMakeFiles/Opengl.dir/RenderObject/Plane.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/RenderObject/Plane.cc.o: ../RenderObject/Plane.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Opengl.dir/RenderObject/Plane.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/RenderObject/Plane.cc.o -c /Users/virgil/Opengl/RenderObject/Plane.cc

CMakeFiles/Opengl.dir/RenderObject/Plane.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/RenderObject/Plane.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/RenderObject/Plane.cc > CMakeFiles/Opengl.dir/RenderObject/Plane.cc.i

CMakeFiles/Opengl.dir/RenderObject/Plane.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/RenderObject/Plane.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/RenderObject/Plane.cc -o CMakeFiles/Opengl.dir/RenderObject/Plane.cc.s

CMakeFiles/Opengl.dir/Scene.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Scene.cc.o: ../Scene.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Opengl.dir/Scene.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Scene.cc.o -c /Users/virgil/Opengl/Scene.cc

CMakeFiles/Opengl.dir/Scene.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Scene.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Scene.cc > CMakeFiles/Opengl.dir/Scene.cc.i

CMakeFiles/Opengl.dir/Scene.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Scene.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Scene.cc -o CMakeFiles/Opengl.dir/Scene.cc.s

CMakeFiles/Opengl.dir/RenderObject/Box.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/RenderObject/Box.cc.o: ../RenderObject/Box.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Opengl.dir/RenderObject/Box.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/RenderObject/Box.cc.o -c /Users/virgil/Opengl/RenderObject/Box.cc

CMakeFiles/Opengl.dir/RenderObject/Box.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/RenderObject/Box.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/RenderObject/Box.cc > CMakeFiles/Opengl.dir/RenderObject/Box.cc.i

CMakeFiles/Opengl.dir/RenderObject/Box.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/RenderObject/Box.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/RenderObject/Box.cc -o CMakeFiles/Opengl.dir/RenderObject/Box.cc.s

CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.o: ../RenderObject/Sphere.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.o -c /Users/virgil/Opengl/RenderObject/Sphere.cc

CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/RenderObject/Sphere.cc > CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.i

CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/RenderObject/Sphere.cc -o CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.s

CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.o: ../RenderPass/ShadowProcess.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.o -c /Users/virgil/Opengl/RenderPass/ShadowProcess.cc

CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/RenderPass/ShadowProcess.cc > CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.i

CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/RenderPass/ShadowProcess.cc -o CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.s

CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.o: ../RenderPass/ColorCubeProcess.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.o -c /Users/virgil/Opengl/RenderPass/ColorCubeProcess.cc

CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/RenderPass/ColorCubeProcess.cc > CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.i

CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/RenderPass/ColorCubeProcess.cc -o CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.s

CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.o: ../RenderPass/HDRProcess.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.o -c /Users/virgil/Opengl/RenderPass/HDRProcess.cc

CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/RenderPass/HDRProcess.cc > CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.i

CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/RenderPass/HDRProcess.cc -o CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.s

CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.o: ../RenderPass/BasicQuadProcess.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.o -c /Users/virgil/Opengl/RenderPass/BasicQuadProcess.cc

CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/RenderPass/BasicQuadProcess.cc > CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.i

CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/RenderPass/BasicQuadProcess.cc -o CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.s

CMakeFiles/Opengl.dir/Model/Model.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Model/Model.cc.o: ../Model/Model.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/Opengl.dir/Model/Model.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Model/Model.cc.o -c /Users/virgil/Opengl/Model/Model.cc

CMakeFiles/Opengl.dir/Model/Model.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Model/Model.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Model/Model.cc > CMakeFiles/Opengl.dir/Model/Model.cc.i

CMakeFiles/Opengl.dir/Model/Model.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Model/Model.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Model/Model.cc -o CMakeFiles/Opengl.dir/Model/Model.cc.s

CMakeFiles/Opengl.dir/Model/Mesh.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Model/Mesh.cc.o: ../Model/Mesh.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/Opengl.dir/Model/Mesh.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Model/Mesh.cc.o -c /Users/virgil/Opengl/Model/Mesh.cc

CMakeFiles/Opengl.dir/Model/Mesh.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Model/Mesh.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Model/Mesh.cc > CMakeFiles/Opengl.dir/Model/Mesh.cc.i

CMakeFiles/Opengl.dir/Model/Mesh.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Model/Mesh.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Model/Mesh.cc -o CMakeFiles/Opengl.dir/Model/Mesh.cc.s

# Object files for target Opengl
Opengl_OBJECTS = \
"CMakeFiles/Opengl.dir/main.cpp.o" \
"CMakeFiles/Opengl.dir/window/Window.cc.o" \
"CMakeFiles/Opengl.dir/Thread/Task.cc.o" \
"CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.o" \
"CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o" \
"CMakeFiles/Opengl.dir/Log/LogUtil.cc.o" \
"CMakeFiles/Opengl.dir/Shader.cc.o" \
"CMakeFiles/Opengl.dir/Texture2D.cc.o" \
"CMakeFiles/Opengl.dir/ResourceManager.cc.o" \
"CMakeFiles/Opengl.dir/RenderObject/Plane.cc.o" \
"CMakeFiles/Opengl.dir/Scene.cc.o" \
"CMakeFiles/Opengl.dir/RenderObject/Box.cc.o" \
"CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.o" \
"CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.o" \
"CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.o" \
"CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.o" \
"CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.o" \
"CMakeFiles/Opengl.dir/Model/Model.cc.o" \
"CMakeFiles/Opengl.dir/Model/Mesh.cc.o"

# External object files for target Opengl
Opengl_EXTERNAL_OBJECTS =

Opengl: CMakeFiles/Opengl.dir/main.cpp.o
Opengl: CMakeFiles/Opengl.dir/window/Window.cc.o
Opengl: CMakeFiles/Opengl.dir/Thread/Task.cc.o
Opengl: CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.o
Opengl: CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o
Opengl: CMakeFiles/Opengl.dir/Log/LogUtil.cc.o
Opengl: CMakeFiles/Opengl.dir/Shader.cc.o
Opengl: CMakeFiles/Opengl.dir/Texture2D.cc.o
Opengl: CMakeFiles/Opengl.dir/ResourceManager.cc.o
Opengl: CMakeFiles/Opengl.dir/RenderObject/Plane.cc.o
Opengl: CMakeFiles/Opengl.dir/Scene.cc.o
Opengl: CMakeFiles/Opengl.dir/RenderObject/Box.cc.o
Opengl: CMakeFiles/Opengl.dir/RenderObject/Sphere.cc.o
Opengl: CMakeFiles/Opengl.dir/RenderPass/ShadowProcess.cc.o
Opengl: CMakeFiles/Opengl.dir/RenderPass/ColorCubeProcess.cc.o
Opengl: CMakeFiles/Opengl.dir/RenderPass/HDRProcess.cc.o
Opengl: CMakeFiles/Opengl.dir/RenderPass/BasicQuadProcess.cc.o
Opengl: CMakeFiles/Opengl.dir/Model/Model.cc.o
Opengl: CMakeFiles/Opengl.dir/Model/Mesh.cc.o
Opengl: CMakeFiles/Opengl.dir/build.make
Opengl: /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib
Opengl: /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.dylib
Opengl: /usr/local/Cellar/assimp/5.0.1/lib/libassimp.5.dylib
Opengl: CMakeFiles/Opengl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Linking CXX executable Opengl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Opengl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Opengl.dir/build: Opengl

.PHONY : CMakeFiles/Opengl.dir/build

CMakeFiles/Opengl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Opengl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Opengl.dir/clean

CMakeFiles/Opengl.dir/depend:
	cd /Users/virgil/Opengl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/virgil/Opengl /Users/virgil/Opengl /Users/virgil/Opengl/cmake-build-debug /Users/virgil/Opengl/cmake-build-debug /Users/virgil/Opengl/cmake-build-debug/CMakeFiles/Opengl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Opengl.dir/depend

