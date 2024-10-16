add_library(detector_lib STATIC detector.hpp implement.cpp)
target_include_directories(detector_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
