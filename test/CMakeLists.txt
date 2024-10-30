# Any C++ source files needed to build this target (cpp-test).
add_executable(cpp-test
  # list of source cpp files:
  main.cpp
  test.cpp
)

# Any dependent libraries needed to build this target.
target_link_libraries(cpp-test PUBLIC
  # list of libraries:
  gtest
  detector_lib
)

# Include the directory for Tracker
target_include_directories(cpp-test PRIVATE ${PROJECT_SOURCE_DIR}/libs/Tracker)

# Include the directory for Detector
target_include_directories(cpp-test PRIVATE ${PROJECT_SOURCE_DIR}/libs/Detector)

# Enable CMake’s test runner to discover the tests included in the binary
gtest_discover_tests(cpp-test)
