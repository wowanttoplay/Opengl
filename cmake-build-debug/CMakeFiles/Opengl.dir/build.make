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

CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.o: ../shader/ShaderFactory.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.o -c /Users/virgil/Opengl/shader/ShaderFactory.cc

CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/shader/ShaderFactory.cc > CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.i

CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/shader/ShaderFactory.cc -o CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.s

CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o: ../Tool/PrintTool.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o -c /Users/virgil/Opengl/Tool/PrintTool.cc

CMakeFiles/Opengl.dir/Tool/PrintTool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Tool/PrintTool.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Tool/PrintTool.cc > CMakeFiles/Opengl.dir/Tool/PrintTool.cc.i

CMakeFiles/Opengl.dir/Tool/PrintTool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Tool/PrintTool.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Tool/PrintTool.cc -o CMakeFiles/Opengl.dir/Tool/PrintTool.cc.s

CMakeFiles/Opengl.dir/Log/LogUtil.cc.o: CMakeFiles/Opengl.dir/flags.make
CMakeFiles/Opengl.dir/Log/LogUtil.cc.o: ../Log/LogUtil.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Opengl.dir/Log/LogUtil.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Opengl.dir/Log/LogUtil.cc.o -c /Users/virgil/Opengl/Log/LogUtil.cc

CMakeFiles/Opengl.dir/Log/LogUtil.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Opengl.dir/Log/LogUtil.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/virgil/Opengl/Log/LogUtil.cc > CMakeFiles/Opengl.dir/Log/LogUtil.cc.i

CMakeFiles/Opengl.dir/Log/LogUtil.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Opengl.dir/Log/LogUtil.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/virgil/Opengl/Log/LogUtil.cc -o CMakeFiles/Opengl.dir/Log/LogUtil.cc.s

# Object files for target Opengl
Opengl_OBJECTS = \
"CMakeFiles/Opengl.dir/main.cpp.o" \
"CMakeFiles/Opengl.dir/window/Window.cc.o" \
"CMakeFiles/Opengl.dir/Thread/Task.cc.o" \
"CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.o" \
"CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.o" \
"CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o" \
"CMakeFiles/Opengl.dir/Log/LogUtil.cc.o"

# External object files for target Opengl
Opengl_EXTERNAL_OBJECTS =

Opengl: CMakeFiles/Opengl.dir/main.cpp.o
Opengl: CMakeFiles/Opengl.dir/window/Window.cc.o
Opengl: CMakeFiles/Opengl.dir/Thread/Task.cc.o
Opengl: CMakeFiles/Opengl.dir/Thread/ThreadPool.cc.o
Opengl: CMakeFiles/Opengl.dir/shader/ShaderFactory.cc.o
Opengl: CMakeFiles/Opengl.dir/Tool/PrintTool.cc.o
Opengl: CMakeFiles/Opengl.dir/Log/LogUtil.cc.o
Opengl: CMakeFiles/Opengl.dir/build.make
Opengl: /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib
Opengl: /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.dylib
Opengl: CMakeFiles/Opengl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/virgil/Opengl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Opengl"
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

