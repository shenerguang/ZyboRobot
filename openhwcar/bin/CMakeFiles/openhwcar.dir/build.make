# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/openhwcar/bin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/openhwcar/bin

# Include any dependencies generated for this target.
include CMakeFiles/openhwcar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/openhwcar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/openhwcar.dir/flags.make

CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o: CMakeFiles/openhwcar.dir/flags.make
CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o: /root/openhwcar/src/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/openhwcar/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o   -c /root/openhwcar/src/main.c

CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /root/openhwcar/src/main.c > CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.i

CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /root/openhwcar/src/main.c -o CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.s

CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o.requires:
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o.requires

CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o.provides: CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/openhwcar.dir/build.make CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o.provides.build
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o.provides

CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o.provides.build: CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o

CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o: CMakeFiles/openhwcar.dir/flags.make
CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o: /root/openhwcar/src/eye.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/openhwcar/bin/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o   -c /root/openhwcar/src/eye.c

CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /root/openhwcar/src/eye.c > CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.i

CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /root/openhwcar/src/eye.c -o CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.s

CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o.requires:
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o.requires

CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o.provides: CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o.requires
	$(MAKE) -f CMakeFiles/openhwcar.dir/build.make CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o.provides.build
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o.provides

CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o.provides.build: CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o

CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o: CMakeFiles/openhwcar.dir/flags.make
CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o: /root/openhwcar/src/motor.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/openhwcar/bin/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o   -c /root/openhwcar/src/motor.c

CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /root/openhwcar/src/motor.c > CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.i

CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /root/openhwcar/src/motor.c -o CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.s

CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o.requires:
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o.requires

CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o.provides: CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o.requires
	$(MAKE) -f CMakeFiles/openhwcar.dir/build.make CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o.provides.build
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o.provides

CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o.provides.build: CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o

CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o: CMakeFiles/openhwcar.dir/flags.make
CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o: /root/openhwcar/src/roadctl.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/openhwcar/bin/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o   -c /root/openhwcar/src/roadctl.c

CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /root/openhwcar/src/roadctl.c > CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.i

CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /root/openhwcar/src/roadctl.c -o CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.s

CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o.requires:
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o.requires

CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o.provides: CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o.requires
	$(MAKE) -f CMakeFiles/openhwcar.dir/build.make CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o.provides.build
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o.provides

CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o.provides.build: CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o

CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o: CMakeFiles/openhwcar.dir/flags.make
CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o: /root/openhwcar/src/sign.c
	$(CMAKE_COMMAND) -E cmake_progress_report /root/openhwcar/bin/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o   -c /root/openhwcar/src/sign.c

CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /root/openhwcar/src/sign.c > CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.i

CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /root/openhwcar/src/sign.c -o CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.s

CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o.requires:
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o.requires

CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o.provides: CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o.requires
	$(MAKE) -f CMakeFiles/openhwcar.dir/build.make CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o.provides.build
.PHONY : CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o.provides

CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o.provides.build: CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o

# Object files for target openhwcar
openhwcar_OBJECTS = \
"CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o" \
"CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o" \
"CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o" \
"CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o" \
"CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o"

# External object files for target openhwcar
openhwcar_EXTERNAL_OBJECTS =

openhwcar: CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o
openhwcar: CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o
openhwcar: CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o
openhwcar: CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o
openhwcar: CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o
openhwcar: /usr/local/lib/libopencv_videostab.so.2.4.9
openhwcar: /usr/local/lib/libopencv_video.so.2.4.9
openhwcar: /usr/local/lib/libopencv_ts.a
openhwcar: /usr/local/lib/libopencv_superres.so.2.4.9
openhwcar: /usr/local/lib/libopencv_stitching.so.2.4.9
openhwcar: /usr/local/lib/libopencv_photo.so.2.4.9
openhwcar: /usr/local/lib/libopencv_ocl.so.2.4.9
openhwcar: /usr/local/lib/libopencv_objdetect.so.2.4.9
openhwcar: /usr/local/lib/libopencv_nonfree.so.2.4.9
openhwcar: /usr/local/lib/libopencv_ml.so.2.4.9
openhwcar: /usr/local/lib/libopencv_legacy.so.2.4.9
openhwcar: /usr/local/lib/libopencv_imgproc.so.2.4.9
openhwcar: /usr/local/lib/libopencv_highgui.so.2.4.9
openhwcar: /usr/local/lib/libopencv_gpu.so.2.4.9
openhwcar: /usr/local/lib/libopencv_flann.so.2.4.9
openhwcar: /usr/local/lib/libopencv_features2d.so.2.4.9
openhwcar: /usr/local/lib/libopencv_core.so.2.4.9
openhwcar: /usr/local/lib/libopencv_contrib.so.2.4.9
openhwcar: /usr/local/lib/libopencv_calib3d.so.2.4.9
openhwcar: /usr/local/lib/libopencv_nonfree.so.2.4.9
openhwcar: /usr/local/lib/libopencv_ocl.so.2.4.9
openhwcar: /usr/local/lib/libopencv_gpu.so.2.4.9
openhwcar: /usr/local/lib/libopencv_photo.so.2.4.9
openhwcar: /usr/local/lib/libopencv_objdetect.so.2.4.9
openhwcar: /usr/local/lib/libopencv_legacy.so.2.4.9
openhwcar: /usr/local/lib/libopencv_video.so.2.4.9
openhwcar: /usr/local/lib/libopencv_ml.so.2.4.9
openhwcar: /usr/local/lib/libopencv_calib3d.so.2.4.9
openhwcar: /usr/local/lib/libopencv_features2d.so.2.4.9
openhwcar: /usr/local/lib/libopencv_highgui.so.2.4.9
openhwcar: /usr/local/lib/libopencv_imgproc.so.2.4.9
openhwcar: /usr/local/lib/libopencv_flann.so.2.4.9
openhwcar: /usr/local/lib/libopencv_core.so.2.4.9
openhwcar: CMakeFiles/openhwcar.dir/build.make
openhwcar: CMakeFiles/openhwcar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable openhwcar"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/openhwcar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/openhwcar.dir/build: openhwcar
.PHONY : CMakeFiles/openhwcar.dir/build

CMakeFiles/openhwcar.dir/requires: CMakeFiles/openhwcar.dir/root/openhwcar/src/main.c.o.requires
CMakeFiles/openhwcar.dir/requires: CMakeFiles/openhwcar.dir/root/openhwcar/src/eye.c.o.requires
CMakeFiles/openhwcar.dir/requires: CMakeFiles/openhwcar.dir/root/openhwcar/src/motor.c.o.requires
CMakeFiles/openhwcar.dir/requires: CMakeFiles/openhwcar.dir/root/openhwcar/src/roadctl.c.o.requires
CMakeFiles/openhwcar.dir/requires: CMakeFiles/openhwcar.dir/root/openhwcar/src/sign.c.o.requires
.PHONY : CMakeFiles/openhwcar.dir/requires

CMakeFiles/openhwcar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/openhwcar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/openhwcar.dir/clean

CMakeFiles/openhwcar.dir/depend:
	cd /root/openhwcar/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/openhwcar/bin /root/openhwcar/bin /root/openhwcar/bin /root/openhwcar/bin /root/openhwcar/bin/CMakeFiles/openhwcar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/openhwcar.dir/depend

