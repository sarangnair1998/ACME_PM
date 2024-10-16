# Any C++ source files needed to build this target (shell-app).
add_executable(acme_pm
  # list of source cpp files:
  main.cpp
  )


# Any dependent libraires needed to build this target.
target_link_libraries(acme_pm PUBLIC
  # list of libraries:
  detector_lib
  tracker_lib
  )
