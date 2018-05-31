# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Desktop/arduino-cuber

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/arduino-cuber

# Include any dependencies generated for this target.
include CMakeFiles/tilapia.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tilapia.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tilapia.dir/flags.make

CMakeFiles/tilapia.dir/tilapia.cpp.o: CMakeFiles/tilapia.dir/flags.make
CMakeFiles/tilapia.dir/tilapia.cpp.o: tilapia.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/arduino-cuber/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tilapia.dir/tilapia.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tilapia.dir/tilapia.cpp.o -c /home/pi/Desktop/arduino-cuber/tilapia.cpp

CMakeFiles/tilapia.dir/tilapia.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tilapia.dir/tilapia.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/arduino-cuber/tilapia.cpp > CMakeFiles/tilapia.dir/tilapia.cpp.i

CMakeFiles/tilapia.dir/tilapia.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tilapia.dir/tilapia.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/arduino-cuber/tilapia.cpp -o CMakeFiles/tilapia.dir/tilapia.cpp.s

CMakeFiles/tilapia.dir/tilapia.cpp.o.requires:

.PHONY : CMakeFiles/tilapia.dir/tilapia.cpp.o.requires

CMakeFiles/tilapia.dir/tilapia.cpp.o.provides: CMakeFiles/tilapia.dir/tilapia.cpp.o.requires
	$(MAKE) -f CMakeFiles/tilapia.dir/build.make CMakeFiles/tilapia.dir/tilapia.cpp.o.provides.build
.PHONY : CMakeFiles/tilapia.dir/tilapia.cpp.o.provides

CMakeFiles/tilapia.dir/tilapia.cpp.o.provides.build: CMakeFiles/tilapia.dir/tilapia.cpp.o


# Object files for target tilapia
tilapia_OBJECTS = \
"CMakeFiles/tilapia.dir/tilapia.cpp.o"

# External object files for target tilapia
tilapia_EXTERNAL_OBJECTS =

tilapia: CMakeFiles/tilapia.dir/tilapia.cpp.o
tilapia: CMakeFiles/tilapia.dir/build.make
tilapia: /usr/local/lib/libopencv_shape.so.3.2.0
tilapia: /usr/local/lib/libopencv_stitching.so.3.2.0
tilapia: /usr/local/lib/libopencv_superres.so.3.2.0
tilapia: /usr/local/lib/libopencv_videostab.so.3.2.0
tilapia: /usr/local/lib/libopencv_objdetect.so.3.2.0
tilapia: /usr/local/lib/libopencv_calib3d.so.3.2.0
tilapia: /usr/local/lib/libopencv_features2d.so.3.2.0
tilapia: /usr/local/lib/libopencv_flann.so.3.2.0
tilapia: /usr/local/lib/libopencv_highgui.so.3.2.0
tilapia: /usr/local/lib/libopencv_ml.so.3.2.0
tilapia: /usr/local/lib/libopencv_photo.so.3.2.0
tilapia: /usr/local/lib/libopencv_video.so.3.2.0
tilapia: /usr/local/lib/libopencv_videoio.so.3.2.0
tilapia: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
tilapia: /usr/local/lib/libopencv_imgproc.so.3.2.0
tilapia: /usr/local/lib/libopencv_core.so.3.2.0
tilapia: CMakeFiles/tilapia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/arduino-cuber/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tilapia"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tilapia.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tilapia.dir/build: tilapia

.PHONY : CMakeFiles/tilapia.dir/build

CMakeFiles/tilapia.dir/requires: CMakeFiles/tilapia.dir/tilapia.cpp.o.requires

.PHONY : CMakeFiles/tilapia.dir/requires

CMakeFiles/tilapia.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tilapia.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tilapia.dir/clean

CMakeFiles/tilapia.dir/depend:
	cd /home/pi/Desktop/arduino-cuber && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/arduino-cuber /home/pi/Desktop/arduino-cuber /home/pi/Desktop/arduino-cuber /home/pi/Desktop/arduino-cuber /home/pi/Desktop/arduino-cuber/CMakeFiles/tilapia.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tilapia.dir/depend
