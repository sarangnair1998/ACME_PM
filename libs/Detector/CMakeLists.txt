# add_library(detector_lib STATIC detector.hpp implement.cpp)
# target_include_directories(detector_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# Declare the executable/library or target in this subdirectory
add_library(detector_lib implement.cpp)

# Link OpenCV libraries to this target
target_link_libraries(detector_lib ${OpenCV_LIBS})

# If you need to include directories specifically for this folder:
include_directories(${OpenCV_INCLUDE_DIRS})