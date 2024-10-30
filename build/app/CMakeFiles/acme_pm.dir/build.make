# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build

# Include any dependencies generated for this target.
include app/CMakeFiles/acme_pm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include app/CMakeFiles/acme_pm.dir/compiler_depend.make

# Include the progress variables for this target.
include app/CMakeFiles/acme_pm.dir/progress.make

# Include the compile flags for this target's objects.
include app/CMakeFiles/acme_pm.dir/flags.make

app/CMakeFiles/acme_pm.dir/main.cpp.o: app/CMakeFiles/acme_pm.dir/flags.make
app/CMakeFiles/acme_pm.dir/main.cpp.o: ../app/main.cpp
app/CMakeFiles/acme_pm.dir/main.cpp.o: app/CMakeFiles/acme_pm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object app/CMakeFiles/acme_pm.dir/main.cpp.o"
	cd /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build/app && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT app/CMakeFiles/acme_pm.dir/main.cpp.o -MF CMakeFiles/acme_pm.dir/main.cpp.o.d -o CMakeFiles/acme_pm.dir/main.cpp.o -c /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/app/main.cpp

app/CMakeFiles/acme_pm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/acme_pm.dir/main.cpp.i"
	cd /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build/app && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/app/main.cpp > CMakeFiles/acme_pm.dir/main.cpp.i

app/CMakeFiles/acme_pm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/acme_pm.dir/main.cpp.s"
	cd /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build/app && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/app/main.cpp -o CMakeFiles/acme_pm.dir/main.cpp.s

# Object files for target acme_pm
acme_pm_OBJECTS = \
"CMakeFiles/acme_pm.dir/main.cpp.o"

# External object files for target acme_pm
acme_pm_EXTERNAL_OBJECTS =

app/acme_pm: app/CMakeFiles/acme_pm.dir/main.cpp.o
app/acme_pm: app/CMakeFiles/acme_pm.dir/build.make
app/acme_pm: libs/Detector/libdetector_lib.a
app/acme_pm: libs/Tracker/libtracker_lib.a
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_alphamat.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_barcode.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_dnn_objdetect.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_dnn_superres.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_face.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_hfs.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_img_hash.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_intensity_transform.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_mcc.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_quality.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_rapid.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_tracking.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_text.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_wechat_qrcode.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_video.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_dnn.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.5.4d
app/acme_pm: /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.5.4d
app/acme_pm: app/CMakeFiles/acme_pm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable acme_pm"
	cd /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build/app && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/acme_pm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
app/CMakeFiles/acme_pm.dir/build: app/acme_pm
.PHONY : app/CMakeFiles/acme_pm.dir/build

app/CMakeFiles/acme_pm.dir/clean:
	cd /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build/app && $(CMAKE_COMMAND) -P CMakeFiles/acme_pm.dir/cmake_clean.cmake
.PHONY : app/CMakeFiles/acme_pm.dir/clean

app/CMakeFiles/acme_pm.dir/depend:
	cd /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/app /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build/app /home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/build/app/CMakeFiles/acme_pm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : app/CMakeFiles/acme_pm.dir/depend

