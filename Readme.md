![CICD Workflow status](https://github.com/sarangnair1998/ACME_PM/actions/workflows/run-unit-test-and-upload-codecov.yml/badge.svg) 
[![codecov](https://codecov.io/gh/sarangnair1998/ACME_PM/graph/badge.svg?token=KVRGXJYNSB)](https://codecov.io/gh/sarangnair1998/ACME_PM)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)


# Multipurpose Perception Module for ACME 

## Overview
The Multipurpose Perception Module is an advanced object detection and tracking system developed for ACME Robotics. This module leverages the YOLOv3 model to perform real-time human detection using a laptop webcam or a video stream. Built on OpenCV and DNN libraries, the module captures, detects, and tracks human subjects in real-time, providing crucial perception capabilities for autonomous systems in a compact and efficient implementation.

## Key Features
- *Human Detection:* Detects human objects in real-time using the YOLOv3 model.
- *Bounding Box Annotation:* Draws bounding boxes around detected objects with class names and confidence scores.
- *Non-Maximum Suppression (NMS):* Filters overlapping detections to improve accuracy and reduce duplicate bounding boxes.
- *Confidence Thresholding:* Customizable minimum confidence score to filter low-confidence detections.
- *Real-Time Processing:* Processes live video streams from a laptop webcam, displaying results in real-time.
- *Robust Tracking (Future Integration):* Includes an interface for seamless integration with tracking algorithms, allowing consistent tracking of detected objects across frames.

## Technologies Used
- *YOLOv3*: Used for high-performance real-time object detection.
- *OpenCV DNN Module*: Provides an interface for loading and running the YOLO model.
- *C++*: Core programming language used for implementation.
- *CMake*: Used for build management.
- *GitHub*: Version control and collaboration.

## Libraries
- *OpenCV*: Includes the core, highgui, dnn, and videoio modules, enabling image processing, video streaming, and deep learning capabilities.
- *C++ Standard Library*: Provides foundational functionality like I/O operations and string manipulation.

## Installation

Clone the Repository:

```bash

git clone https://github.com/sarangnair1998/ACME_PM.git

# Navigate to the Project Directory:

cd ACME_PM

# Build the Project:
Use CMake to configure and build the project:

  cmake -S ./ -B build/
# To build with debugging information, do:
  cmake -S ./ -B build/ -D CMAKE_BUILD_TYPE=Debug
# Compile and build the project:
  # rebuild only files that are modified since the last build
  cmake --build build/
  # or rebuild everything from scracth
  cmake --build build/ --clean-first
  # to see verbose output, do:
  cmake --build build/ --verbose

# Run program:
  ./build/app/acme_pm
# Clean
  cmake --build build/ --target clean
# Clean and start over:
  rm -rf build/
```

The system will use a connected monocular camera to detect and track humans, providing real-time position data in the robot's reference frame.

## Project Structure

src/: Source code for the perception module.

include/: Header files for the module.

tests/: Unit tests developed using GoogleTest.

CMakeLists.txt: Build configuration file.

## AIP workflow is being followed

The initial product backlog can be found here - https://docs.google.com/spreadsheets/d/19n18qKphQGY4qy_kX4KHc_CbB6oyr3eH/edit?usp=sharing&ouid=104145698794059197837&rtpof=true&sd=true

## Team Members

Sarang Shibu: Driver (Human Detection)

Prathinav Karnala Venkata: Navigator (Human Tracking)

Abhey Sharma: Design Keeper (Ensures adherence to design principles and OOP practices)

## Contributions

We welcome contributions to enhance the Multipurpose Perception Module. Please follow these steps to contribute:

### Fork the Repository

Create a New Branch: (git checkout -b feature-branch)

Commit Changes: (git commit -m 'Add new feature')

Push to Branch: (git push origin feature-branch)

Open a Pull Request

## Video Presentation of our Proposal- Phase 0



https://github.com/user-attachments/assets/322d0d07-f3bc-4b59-b323-c51a00ef10b9


## Video Presentation of our Proposal- Phase 1

Link to our Phase 1 video can be found below

https://youtu.be/aMdScIC5fSo

## Video Presentation of our Proposal- Phase 2 Final

Link to our Phase 2 video can be found below

https://youtu.be/Y-Dt1c40nVQ


## License

This project is licensed under the Apache 2.0 License - see the LICENSE file for details.

## Contact

For any questions or suggestions, please contact:

Sarang Shibu

Prathinav Karnala Venkata

Abhey Sharma
