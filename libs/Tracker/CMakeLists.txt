# Declare the executable/library or target in this subdirectory
add_library(tracker_lib implement.cpp)

# Link OpenCV libraries to this target
target_link_libraries(tracker_lib ${OpenCV_LIBS})

# If you need to include directories specifically for this folder:
include_directories(${OpenCV_INCLUDE_DIRS})
