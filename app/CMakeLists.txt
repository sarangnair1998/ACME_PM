# Any C++ source files needed to build this target (shell-app).
add_executable(acme_pm
  # list of source cpp files:
  main.cpp
  )

# Include the directory for Tracker
target_include_directories(acme_pm PRIVATE ${PROJECT_SOURCE_DIR}/libs/Tracker)

# Include the directory for Detector
target_include_directories(acme_pm PRIVATE ${PROJECT_SOURCE_DIR}/libs/Detector)

# Any dependent libraires needed to build this target.
target_link_libraries(acme_pm PUBLIC
  # list of libraries:
  detector_lib
  tracker_lib
  )
