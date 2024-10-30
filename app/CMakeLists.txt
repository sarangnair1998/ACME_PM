# Any C++ source files needed to build this target (shell-app).
add_executable(acme_pm
  # list of source cpp files:
  main.cpp
  )

# Include the directory for Detector
target_include_directories(acme_pm PRIVATE ${PROJECT_SOURCE_DIR}/libs/Detector)

# Any dependent libraires needed to build this target.
target_link_libraries(acme_pm PUBLIC
  # list of libraries:
  detector_lib
  )

  # Specify the URL for YOLOv3 weights and destination path
set(WEIGHTS_URL "https://pjreddie.com/media/files/yolov3.weights")
set(WEIGHTS_PATH "${CMAKE_SOURCE_DIR}/model/yolov3.weights")

# Create the model directory if it doesn't exist
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/model")

# Download the weights file if it is not already present
if(NOT EXISTS ${WEIGHTS_PATH})
    message(STATUS "Downloading YOLOv3 weights...")
    file(DOWNLOAD ${WEIGHTS_URL} ${WEIGHTS_PATH} SHOW_PROGRESS)
else()
    message(STATUS "YOLOv3 weights already exist.")
endif()

# Add a custom target to manage the download
add_custom_target(download_weights ALL
    DEPENDS ${WEIGHTS_PATH}
)

# Add a dependency to your main target to ensure weights are downloaded first
add_dependencies(acme_pm download_weights)