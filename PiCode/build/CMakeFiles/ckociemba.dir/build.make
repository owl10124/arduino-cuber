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
CMAKE_SOURCE_DIR = /home/pi/Desktop/arduino-cuber/PiCode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/arduino-cuber/PiCode/build

# Include any dependencies generated for this target.
include CMakeFiles/ckociemba.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ckociemba.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ckociemba.dir/flags.make

CMakeFiles/ckociemba.dir/coordcube.c.o: CMakeFiles/ckociemba.dir/flags.make
CMakeFiles/ckociemba.dir/coordcube.c.o: ../coordcube.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/arduino-cuber/PiCode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ckociemba.dir/coordcube.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ckociemba.dir/coordcube.c.o   -c /home/pi/Desktop/arduino-cuber/PiCode/coordcube.c

CMakeFiles/ckociemba.dir/coordcube.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ckociemba.dir/coordcube.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Desktop/arduino-cuber/PiCode/coordcube.c > CMakeFiles/ckociemba.dir/coordcube.c.i

CMakeFiles/ckociemba.dir/coordcube.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ckociemba.dir/coordcube.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Desktop/arduino-cuber/PiCode/coordcube.c -o CMakeFiles/ckociemba.dir/coordcube.c.s

CMakeFiles/ckociemba.dir/coordcube.c.o.requires:

.PHONY : CMakeFiles/ckociemba.dir/coordcube.c.o.requires

CMakeFiles/ckociemba.dir/coordcube.c.o.provides: CMakeFiles/ckociemba.dir/coordcube.c.o.requires
	$(MAKE) -f CMakeFiles/ckociemba.dir/build.make CMakeFiles/ckociemba.dir/coordcube.c.o.provides.build
.PHONY : CMakeFiles/ckociemba.dir/coordcube.c.o.provides

CMakeFiles/ckociemba.dir/coordcube.c.o.provides.build: CMakeFiles/ckociemba.dir/coordcube.c.o


CMakeFiles/ckociemba.dir/cubiecube.c.o: CMakeFiles/ckociemba.dir/flags.make
CMakeFiles/ckociemba.dir/cubiecube.c.o: ../cubiecube.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/arduino-cuber/PiCode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ckociemba.dir/cubiecube.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ckociemba.dir/cubiecube.c.o   -c /home/pi/Desktop/arduino-cuber/PiCode/cubiecube.c

CMakeFiles/ckociemba.dir/cubiecube.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ckociemba.dir/cubiecube.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Desktop/arduino-cuber/PiCode/cubiecube.c > CMakeFiles/ckociemba.dir/cubiecube.c.i

CMakeFiles/ckociemba.dir/cubiecube.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ckociemba.dir/cubiecube.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Desktop/arduino-cuber/PiCode/cubiecube.c -o CMakeFiles/ckociemba.dir/cubiecube.c.s

CMakeFiles/ckociemba.dir/cubiecube.c.o.requires:

.PHONY : CMakeFiles/ckociemba.dir/cubiecube.c.o.requires

CMakeFiles/ckociemba.dir/cubiecube.c.o.provides: CMakeFiles/ckociemba.dir/cubiecube.c.o.requires
	$(MAKE) -f CMakeFiles/ckociemba.dir/build.make CMakeFiles/ckociemba.dir/cubiecube.c.o.provides.build
.PHONY : CMakeFiles/ckociemba.dir/cubiecube.c.o.provides

CMakeFiles/ckociemba.dir/cubiecube.c.o.provides.build: CMakeFiles/ckociemba.dir/cubiecube.c.o


CMakeFiles/ckociemba.dir/facecube.c.o: CMakeFiles/ckociemba.dir/flags.make
CMakeFiles/ckociemba.dir/facecube.c.o: ../facecube.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/arduino-cuber/PiCode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ckociemba.dir/facecube.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ckociemba.dir/facecube.c.o   -c /home/pi/Desktop/arduino-cuber/PiCode/facecube.c

CMakeFiles/ckociemba.dir/facecube.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ckociemba.dir/facecube.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Desktop/arduino-cuber/PiCode/facecube.c > CMakeFiles/ckociemba.dir/facecube.c.i

CMakeFiles/ckociemba.dir/facecube.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ckociemba.dir/facecube.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Desktop/arduino-cuber/PiCode/facecube.c -o CMakeFiles/ckociemba.dir/facecube.c.s

CMakeFiles/ckociemba.dir/facecube.c.o.requires:

.PHONY : CMakeFiles/ckociemba.dir/facecube.c.o.requires

CMakeFiles/ckociemba.dir/facecube.c.o.provides: CMakeFiles/ckociemba.dir/facecube.c.o.requires
	$(MAKE) -f CMakeFiles/ckociemba.dir/build.make CMakeFiles/ckociemba.dir/facecube.c.o.provides.build
.PHONY : CMakeFiles/ckociemba.dir/facecube.c.o.provides

CMakeFiles/ckociemba.dir/facecube.c.o.provides.build: CMakeFiles/ckociemba.dir/facecube.c.o


CMakeFiles/ckociemba.dir/search.c.o: CMakeFiles/ckociemba.dir/flags.make
CMakeFiles/ckociemba.dir/search.c.o: ../search.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/arduino-cuber/PiCode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ckociemba.dir/search.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ckociemba.dir/search.c.o   -c /home/pi/Desktop/arduino-cuber/PiCode/search.c

CMakeFiles/ckociemba.dir/search.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ckociemba.dir/search.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/Desktop/arduino-cuber/PiCode/search.c > CMakeFiles/ckociemba.dir/search.c.i

CMakeFiles/ckociemba.dir/search.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ckociemba.dir/search.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/Desktop/arduino-cuber/PiCode/search.c -o CMakeFiles/ckociemba.dir/search.c.s

CMakeFiles/ckociemba.dir/search.c.o.requires:

.PHONY : CMakeFiles/ckociemba.dir/search.c.o.requires

CMakeFiles/ckociemba.dir/search.c.o.provides: CMakeFiles/ckociemba.dir/search.c.o.requires
	$(MAKE) -f CMakeFiles/ckociemba.dir/build.make CMakeFiles/ckociemba.dir/search.c.o.provides.build
.PHONY : CMakeFiles/ckociemba.dir/search.c.o.provides

CMakeFiles/ckociemba.dir/search.c.o.provides.build: CMakeFiles/ckociemba.dir/search.c.o


CMakeFiles/ckociemba.dir/main.cpp.o: CMakeFiles/ckociemba.dir/flags.make
CMakeFiles/ckociemba.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/arduino-cuber/PiCode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ckociemba.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ckociemba.dir/main.cpp.o -c /home/pi/Desktop/arduino-cuber/PiCode/main.cpp

CMakeFiles/ckociemba.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ckociemba.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/arduino-cuber/PiCode/main.cpp > CMakeFiles/ckociemba.dir/main.cpp.i

CMakeFiles/ckociemba.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ckociemba.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/arduino-cuber/PiCode/main.cpp -o CMakeFiles/ckociemba.dir/main.cpp.s

CMakeFiles/ckociemba.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ckociemba.dir/main.cpp.o.requires

CMakeFiles/ckociemba.dir/main.cpp.o.provides: CMakeFiles/ckociemba.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ckociemba.dir/build.make CMakeFiles/ckociemba.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ckociemba.dir/main.cpp.o.provides

CMakeFiles/ckociemba.dir/main.cpp.o.provides.build: CMakeFiles/ckociemba.dir/main.cpp.o


# Object files for target ckociemba
ckociemba_OBJECTS = \
"CMakeFiles/ckociemba.dir/coordcube.c.o" \
"CMakeFiles/ckociemba.dir/cubiecube.c.o" \
"CMakeFiles/ckociemba.dir/facecube.c.o" \
"CMakeFiles/ckociemba.dir/search.c.o" \
"CMakeFiles/ckociemba.dir/main.cpp.o"

# External object files for target ckociemba
ckociemba_EXTERNAL_OBJECTS =

ckociemba: CMakeFiles/ckociemba.dir/coordcube.c.o
ckociemba: CMakeFiles/ckociemba.dir/cubiecube.c.o
ckociemba: CMakeFiles/ckociemba.dir/facecube.c.o
ckociemba: CMakeFiles/ckociemba.dir/search.c.o
ckociemba: CMakeFiles/ckociemba.dir/main.cpp.o
ckociemba: CMakeFiles/ckociemba.dir/build.make
ckociemba: /opt/vc/lib/libmmal_core.so
ckociemba: /opt/vc/lib/libmmal_util.so
ckociemba: /opt/vc/lib/libmmal.so
ckociemba: /usr/local/lib/libopencv_shape.so.3.2.0
ckociemba: /usr/local/lib/libopencv_stitching.so.3.2.0
ckociemba: /usr/local/lib/libopencv_superres.so.3.2.0
ckociemba: /usr/local/lib/libopencv_videostab.so.3.2.0
ckociemba: /usr/local/lib/libwiringPi.so
ckociemba: /usr/local/lib/libopencv_objdetect.so.3.2.0
ckociemba: /usr/local/lib/libopencv_calib3d.so.3.2.0
ckociemba: /usr/local/lib/libopencv_features2d.so.3.2.0
ckociemba: /usr/local/lib/libopencv_flann.so.3.2.0
ckociemba: /usr/local/lib/libopencv_highgui.so.3.2.0
ckociemba: /usr/local/lib/libopencv_ml.so.3.2.0
ckociemba: /usr/local/lib/libopencv_photo.so.3.2.0
ckociemba: /usr/local/lib/libopencv_video.so.3.2.0
ckociemba: /usr/local/lib/libopencv_videoio.so.3.2.0
ckociemba: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
ckociemba: /usr/local/lib/libopencv_imgproc.so.3.2.0
ckociemba: /usr/local/lib/libopencv_core.so.3.2.0
ckociemba: CMakeFiles/ckociemba.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/arduino-cuber/PiCode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ckociemba"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ckociemba.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ckociemba.dir/build: ckociemba

.PHONY : CMakeFiles/ckociemba.dir/build

CMakeFiles/ckociemba.dir/requires: CMakeFiles/ckociemba.dir/coordcube.c.o.requires
CMakeFiles/ckociemba.dir/requires: CMakeFiles/ckociemba.dir/cubiecube.c.o.requires
CMakeFiles/ckociemba.dir/requires: CMakeFiles/ckociemba.dir/facecube.c.o.requires
CMakeFiles/ckociemba.dir/requires: CMakeFiles/ckociemba.dir/search.c.o.requires
CMakeFiles/ckociemba.dir/requires: CMakeFiles/ckociemba.dir/main.cpp.o.requires

.PHONY : CMakeFiles/ckociemba.dir/requires

CMakeFiles/ckociemba.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ckociemba.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ckociemba.dir/clean

CMakeFiles/ckociemba.dir/depend:
	cd /home/pi/Desktop/arduino-cuber/PiCode/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/arduino-cuber/PiCode /home/pi/Desktop/arduino-cuber/PiCode /home/pi/Desktop/arduino-cuber/PiCode/build /home/pi/Desktop/arduino-cuber/PiCode/build /home/pi/Desktop/arduino-cuber/PiCode/build/CMakeFiles/ckociemba.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ckociemba.dir/depend
