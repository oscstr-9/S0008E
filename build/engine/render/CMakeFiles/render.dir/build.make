# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ogge/Repos/S0017D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ogge/Repos/S0017D/build

# Include any dependencies generated for this target.
include engine/render/CMakeFiles/render.dir/depend.make

# Include the progress variables for this target.
include engine/render/CMakeFiles/render.dir/progress.make

# Include the compile flags for this target's objects.
include engine/render/CMakeFiles/render.dir/flags.make

engine/render/CMakeFiles/render.dir/Camera.cpp.o: engine/render/CMakeFiles/render.dir/flags.make
engine/render/CMakeFiles/render.dir/Camera.cpp.o: ../engine/render/Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object engine/render/CMakeFiles/render.dir/Camera.cpp.o"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/render.dir/Camera.cpp.o -c /home/ogge/Repos/S0017D/engine/render/Camera.cpp

engine/render/CMakeFiles/render.dir/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/render.dir/Camera.cpp.i"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/engine/render/Camera.cpp > CMakeFiles/render.dir/Camera.cpp.i

engine/render/CMakeFiles/render.dir/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/render.dir/Camera.cpp.s"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/engine/render/Camera.cpp -o CMakeFiles/render.dir/Camera.cpp.s

engine/render/CMakeFiles/render.dir/GraphicsNode.cpp.o: engine/render/CMakeFiles/render.dir/flags.make
engine/render/CMakeFiles/render.dir/GraphicsNode.cpp.o: ../engine/render/GraphicsNode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object engine/render/CMakeFiles/render.dir/GraphicsNode.cpp.o"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/render.dir/GraphicsNode.cpp.o -c /home/ogge/Repos/S0017D/engine/render/GraphicsNode.cpp

engine/render/CMakeFiles/render.dir/GraphicsNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/render.dir/GraphicsNode.cpp.i"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/engine/render/GraphicsNode.cpp > CMakeFiles/render.dir/GraphicsNode.cpp.i

engine/render/CMakeFiles/render.dir/GraphicsNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/render.dir/GraphicsNode.cpp.s"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/engine/render/GraphicsNode.cpp -o CMakeFiles/render.dir/GraphicsNode.cpp.s

engine/render/CMakeFiles/render.dir/Lighting.cpp.o: engine/render/CMakeFiles/render.dir/flags.make
engine/render/CMakeFiles/render.dir/Lighting.cpp.o: ../engine/render/Lighting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object engine/render/CMakeFiles/render.dir/Lighting.cpp.o"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/render.dir/Lighting.cpp.o -c /home/ogge/Repos/S0017D/engine/render/Lighting.cpp

engine/render/CMakeFiles/render.dir/Lighting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/render.dir/Lighting.cpp.i"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/engine/render/Lighting.cpp > CMakeFiles/render.dir/Lighting.cpp.i

engine/render/CMakeFiles/render.dir/Lighting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/render.dir/Lighting.cpp.s"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/engine/render/Lighting.cpp -o CMakeFiles/render.dir/Lighting.cpp.s

engine/render/CMakeFiles/render.dir/MeshResource.cpp.o: engine/render/CMakeFiles/render.dir/flags.make
engine/render/CMakeFiles/render.dir/MeshResource.cpp.o: ../engine/render/MeshResource.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object engine/render/CMakeFiles/render.dir/MeshResource.cpp.o"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/render.dir/MeshResource.cpp.o -c /home/ogge/Repos/S0017D/engine/render/MeshResource.cpp

engine/render/CMakeFiles/render.dir/MeshResource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/render.dir/MeshResource.cpp.i"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/engine/render/MeshResource.cpp > CMakeFiles/render.dir/MeshResource.cpp.i

engine/render/CMakeFiles/render.dir/MeshResource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/render.dir/MeshResource.cpp.s"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/engine/render/MeshResource.cpp -o CMakeFiles/render.dir/MeshResource.cpp.s

engine/render/CMakeFiles/render.dir/ShaderResource.cpp.o: engine/render/CMakeFiles/render.dir/flags.make
engine/render/CMakeFiles/render.dir/ShaderResource.cpp.o: ../engine/render/ShaderResource.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object engine/render/CMakeFiles/render.dir/ShaderResource.cpp.o"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/render.dir/ShaderResource.cpp.o -c /home/ogge/Repos/S0017D/engine/render/ShaderResource.cpp

engine/render/CMakeFiles/render.dir/ShaderResource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/render.dir/ShaderResource.cpp.i"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/engine/render/ShaderResource.cpp > CMakeFiles/render.dir/ShaderResource.cpp.i

engine/render/CMakeFiles/render.dir/ShaderResource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/render.dir/ShaderResource.cpp.s"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/engine/render/ShaderResource.cpp -o CMakeFiles/render.dir/ShaderResource.cpp.s

engine/render/CMakeFiles/render.dir/TextureResource.cpp.o: engine/render/CMakeFiles/render.dir/flags.make
engine/render/CMakeFiles/render.dir/TextureResource.cpp.o: ../engine/render/TextureResource.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object engine/render/CMakeFiles/render.dir/TextureResource.cpp.o"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/render.dir/TextureResource.cpp.o -c /home/ogge/Repos/S0017D/engine/render/TextureResource.cpp

engine/render/CMakeFiles/render.dir/TextureResource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/render.dir/TextureResource.cpp.i"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/engine/render/TextureResource.cpp > CMakeFiles/render.dir/TextureResource.cpp.i

engine/render/CMakeFiles/render.dir/TextureResource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/render.dir/TextureResource.cpp.s"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/engine/render/TextureResource.cpp -o CMakeFiles/render.dir/TextureResource.cpp.s

engine/render/CMakeFiles/render.dir/gltfLoader.cpp.o: engine/render/CMakeFiles/render.dir/flags.make
engine/render/CMakeFiles/render.dir/gltfLoader.cpp.o: ../engine/render/gltfLoader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object engine/render/CMakeFiles/render.dir/gltfLoader.cpp.o"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/render.dir/gltfLoader.cpp.o -c /home/ogge/Repos/S0017D/engine/render/gltfLoader.cpp

engine/render/CMakeFiles/render.dir/gltfLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/render.dir/gltfLoader.cpp.i"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/engine/render/gltfLoader.cpp > CMakeFiles/render.dir/gltfLoader.cpp.i

engine/render/CMakeFiles/render.dir/gltfLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/render.dir/gltfLoader.cpp.s"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/engine/render/gltfLoader.cpp -o CMakeFiles/render.dir/gltfLoader.cpp.s

engine/render/CMakeFiles/render.dir/window.cpp.o: engine/render/CMakeFiles/render.dir/flags.make
engine/render/CMakeFiles/render.dir/window.cpp.o: ../engine/render/window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object engine/render/CMakeFiles/render.dir/window.cpp.o"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/render.dir/window.cpp.o -c /home/ogge/Repos/S0017D/engine/render/window.cpp

engine/render/CMakeFiles/render.dir/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/render.dir/window.cpp.i"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/engine/render/window.cpp > CMakeFiles/render.dir/window.cpp.i

engine/render/CMakeFiles/render.dir/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/render.dir/window.cpp.s"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/engine/render/window.cpp -o CMakeFiles/render.dir/window.cpp.s

engine/render/CMakeFiles/render.dir/__/config.cc.o: engine/render/CMakeFiles/render.dir/flags.make
engine/render/CMakeFiles/render.dir/__/config.cc.o: ../engine/config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object engine/render/CMakeFiles/render.dir/__/config.cc.o"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/render.dir/__/config.cc.o -c /home/ogge/Repos/S0017D/engine/config.cc

engine/render/CMakeFiles/render.dir/__/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/render.dir/__/config.cc.i"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ogge/Repos/S0017D/engine/config.cc > CMakeFiles/render.dir/__/config.cc.i

engine/render/CMakeFiles/render.dir/__/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/render.dir/__/config.cc.s"
	cd /home/ogge/Repos/S0017D/build/engine/render && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ogge/Repos/S0017D/engine/config.cc -o CMakeFiles/render.dir/__/config.cc.s

# Object files for target render
render_OBJECTS = \
"CMakeFiles/render.dir/Camera.cpp.o" \
"CMakeFiles/render.dir/GraphicsNode.cpp.o" \
"CMakeFiles/render.dir/Lighting.cpp.o" \
"CMakeFiles/render.dir/MeshResource.cpp.o" \
"CMakeFiles/render.dir/ShaderResource.cpp.o" \
"CMakeFiles/render.dir/TextureResource.cpp.o" \
"CMakeFiles/render.dir/gltfLoader.cpp.o" \
"CMakeFiles/render.dir/window.cpp.o" \
"CMakeFiles/render.dir/__/config.cc.o"

# External object files for target render
render_EXTERNAL_OBJECTS =

engine/render/librender.a: engine/render/CMakeFiles/render.dir/Camera.cpp.o
engine/render/librender.a: engine/render/CMakeFiles/render.dir/GraphicsNode.cpp.o
engine/render/librender.a: engine/render/CMakeFiles/render.dir/Lighting.cpp.o
engine/render/librender.a: engine/render/CMakeFiles/render.dir/MeshResource.cpp.o
engine/render/librender.a: engine/render/CMakeFiles/render.dir/ShaderResource.cpp.o
engine/render/librender.a: engine/render/CMakeFiles/render.dir/TextureResource.cpp.o
engine/render/librender.a: engine/render/CMakeFiles/render.dir/gltfLoader.cpp.o
engine/render/librender.a: engine/render/CMakeFiles/render.dir/window.cpp.o
engine/render/librender.a: engine/render/CMakeFiles/render.dir/__/config.cc.o
engine/render/librender.a: engine/render/CMakeFiles/render.dir/build.make
engine/render/librender.a: engine/render/CMakeFiles/render.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ogge/Repos/S0017D/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library librender.a"
	cd /home/ogge/Repos/S0017D/build/engine/render && $(CMAKE_COMMAND) -P CMakeFiles/render.dir/cmake_clean_target.cmake
	cd /home/ogge/Repos/S0017D/build/engine/render && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/render.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
engine/render/CMakeFiles/render.dir/build: engine/render/librender.a

.PHONY : engine/render/CMakeFiles/render.dir/build

engine/render/CMakeFiles/render.dir/clean:
	cd /home/ogge/Repos/S0017D/build/engine/render && $(CMAKE_COMMAND) -P CMakeFiles/render.dir/cmake_clean.cmake
.PHONY : engine/render/CMakeFiles/render.dir/clean

engine/render/CMakeFiles/render.dir/depend:
	cd /home/ogge/Repos/S0017D/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ogge/Repos/S0017D /home/ogge/Repos/S0017D/engine/render /home/ogge/Repos/S0017D/build /home/ogge/Repos/S0017D/build/engine/render /home/ogge/Repos/S0017D/build/engine/render/CMakeFiles/render.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : engine/render/CMakeFiles/render.dir/depend

