add_library(tracker_lib STATIC tracker.hpp implement.cpp)
target_include_directories(tracker_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
