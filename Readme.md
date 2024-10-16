![CICD Workflow status](https://github.com/sarangnair1998/ACME_PM/actions/workflows/run-unit-test-and-upload-codecov.yml/badge.svg) 
[![codecov](https://codecov.io/gh/sarangnair1998/ACME_PM/branch/main/graph/badge.svg)](https://codecov.io/gh/sarangnair1998/ACME_PM) 
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)


# Multipurpose Perception Module for Acme

## Overview

The Multipurpose Perception Module is a versatile system designed to enhance the perception capabilities of Acme's robotic platforms by detecting and tracking one or more humans in real-time using a monocular camera. The module uses a pre-trained YOLOv4 model for human detection and a Kalman filter for tracking, providing reliable human location data that can be used for efficient navigation and safe interaction in dynamic environments.

## Key Features

- Real-Time Human Detection: Uses YOLOv4 to accurately detect humans in the video stream.

- Human Tracking: Employs Kalman filters to estimate smooth human trajectories and ensure stable tracking.

- Coordinate Transformation: Provides location data in the robot's reference frame for effective path planning.

## Technologies Used

Programming Language: C++ for high efficiency and real-time performance.

Build System: CMake for managing project builds and dependencies.

## Libraries:

OpenCV: For image processing and video handling.

GoogleTest: For unit testing to ensure code quality.

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

##Video Presentation of our Proposal



https://github.com/user-attachments/assets/322d0d07-f3bc-4b59-b323-c51a00ef10b9




## License

This project is licensed under the Apache 2.0 License - see the LICENSE file for details.

## Contact

For any questions or suggestions, please contact:

Sarang Shibu

Prathinav Karnala Venkata

Abhey Sharma
