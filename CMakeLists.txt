cmake_minimum_required(VERSION 3.14)
project(ACME_PM)

# GoogleTest Setup
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Declare a dependency on GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enables testing for this directory and below
enable_testing()
include(GoogleTest)

# Doxygen Support
find_package(Doxygen)
if (DOXYGEN_FOUND)
  set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/docs)
  set(DOXYGEN_COLLABORATION_GRAPH YES)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_CLASS_DIAGRAMS YES)
  set(DOXYGEN_HIDE_UNDOC_RELATIONS NO)
  set(DOXYGEN_HAVE_DOT YES)
  set(DOXYGEN_CLASS_GRAPH YES)
  set(DOXYGEN_CALL_GRAPH YES)
  set(DOXYGEN_CALLER_GRAPH YES)
  set(DOXYGEN_COLLABORATION_GRAPH YES)
  set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
  set(DOXYGEN_EXTRACT_PRIVATE YES)
  set(DOXYGEN_EXTRACT_PACKAGE YES)
  set(DOXYGEN_EXTRACT_STATIC YES)
  set(DOXYGEN_EXTRACT_LOCALMETHODS YES)
  set(DOXYGEN_UML_LOOK YES)
  set(DOXYGEN_UML_LIMIT_NUM_FIELDS 50)
  set(DOXYGEN_TEMPLATE_RELATIONS YES)
  set(DOXYGEN_DOT_GRAPH_MAX_NODES 100)
  set(DOXYGEN_MAX_DOT_GRAPH_DEPTH 0)
  set(DOXYGEN_DOT_TRANSPARENT YES)
else()
  message(FATAL_ERROR "Doxygen needs to be installed to generate the doxygen documentation")
endif()

# Create the compilation database for clangd and move it out of the build dir
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(COMMAND cmake -E create_symlink
  "${PROJECT_BINARY_DIR}/compile_commands.json"
  "${PROJECT_SOURCE_DIR}/compile_commands.json")

# Code coverage generation
option(WANT_COVERAGE "this option enable coverage" ON)
if(NOT CMAKE_BUILD_TYPE MATCHES "Debug")
  set(WANT_COVERAGE OFF)
endif()

if(WANT_COVERAGE)
  message("Enabling coverage")
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")
  include(CodeCoverage)
  append_coverage_compiler_flags()
  set(COVERAGE_EXCLUDES
    ${PROJECT_BINARY_DIR}
  )
endif()

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add subdirectories (Only once, using unique binary directories)
add_subdirectory(app ${CMAKE_BINARY_DIR}/app)
add_subdirectory(libs ${CMAKE_BINARY_DIR}/libs)
add_subdirectory(test ${CMAKE_BINARY_DIR}/test)

# Doxygen target
doxygen_add_docs(docs
  ${PROJECT_SOURCE_DIR}/app
  ${PROJECT_SOURCE_DIR}/libs
  ${PROJECT_SOURCE_DIR}/include
)

# Code coverage targets
if(WANT_COVERAGE)
  # Unit test coverage:
  setup_target_for_coverage_lcov(
    NAME test_coverage
    # EXECUTABLE ctest
    EXECUTABLE cpp-test

    EXCLUDE
      "app/main.cpp"
      "*gtest*"
      "/usr/include/*"
  )
  
  # Code coverage for the app (shell-app):
  setup_target_for_coverage_gcovr_html(
    NAME app_coverage
    EXECUTABLE shell-app
    EXCLUDE
      "test/test.cpp"
      "test/main.cpp"
  )
endif()

# Sanity check
message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(STATUS "WANT_COVERAGE    = ${WANT_COVERAGE}")
