// Copyright [2024] Abhey Sharma, Prathinav K V, Sarang Nair

/**
 * @file main.cpp
 * @brief Main program for initializing the YOLODetector and running the video
 * stream.
 *
 * This program checks for the existence of YOLO configuration, weights, and
 * labels files. If the required files are found, it initializes the
 * YOLODetector and starts the video stream for object detection. It handles any
 * runtime or OpenCV exceptions that occur during initialization.
 */

#include <fstream>
#include <iostream>

#include "detector.hpp"

int main() {
  /**< Path to YOLO configuration file */
  std::string configPath = "./config/yolov3.cfg";
  /**< Path to YOLO weights file */
  std::string weightsPath = "./model/yolov3.weights";
  /**< Path to labels file containing class names */
  std::string labelsPath = "./labels/coco.names";

  // Check if configuration file exists
  std::ifstream configFile(configPath);
  if (!configFile.good()) {
    std::cerr << "Error: Configuration file not found at " << configPath
              << std::endl;
    return -1;
  }

  // Check if weights file exists
  std::ifstream weightsFile(weightsPath);
  if (!weightsFile.good()) {
    std::cerr << "Error: Weights file not found at " << weightsPath
              << std::endl;
    return -1;
  }

  // Check if labels file exists
  std::ifstream labelsFile(labelsPath);
  if (!labelsFile.good()) {
    std::cerr << "Error: Labels file not found at " << labelsPath << std::endl;
    return -1;
  }

  try {
    /**
     * @brief Initializes the YOLODetector with the given configuration,
     * weights, and labels files. Starts the video stream for object detection.
     */
    Detector::YOLODetector detector(configPath, weightsPath, labelsPath);
    detector.videoStream();
  } catch (const cv::Exception& e) {
    std::cerr << "OpenCV Error: " << e.what() << std::endl;
    return -1;
  } catch (const std::runtime_error& e) {
    std::cerr << "Runtime Error: " << e.what() << std::endl;
    return -1;
  }

  return 0;
}
