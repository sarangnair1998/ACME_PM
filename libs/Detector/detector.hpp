// Copyright [2024] Abhey Sharma, Prathinav K V, Sarang Nair
#pragma once

/**
 * @file detector.hpp
 * @brief Header file for the YOLODetector class using YOLOv3 for object
 * detection.
 */

#include <cstddef>
#include <fstream>
#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <vector>

namespace Detector {

/**
 * @class YOLODetector
 * @brief A class for performing object detection using YOLOv3.
 */
class YOLODetector {
 public:
  /**
   * @brief Constructs a YOLODetector object.
   * @param configPath Path to the YOLO configuration file.
   * @param weightsPath Path to the YOLO weights file.
   * @param classesPath Path to the file containing class names.
   */
  YOLODetector(const std::string& configPath, const std::string& weightsPath,
               const std::string& classesPath);

  /**
   * @brief Starts the video stream for object detection.
   * @param testMode If true, enables test mode for the video stream.
   */
  void videoStream(bool testMode = false);

  /**
   * @brief Gets the YOLO network object.
   * @return A constant reference to the cv::dnn::Net object.
   */
  const cv::dnn::Net& getNet() const;

  /**
   * @brief Draws a bounding box and label for a detected object on a frame.
   * @param classId The ID of the detected object's class.
   * @param conf The confidence score of the detection.
   * @param left The x-coordinate of the left side of the bounding box.
   * @param top The y-coordinate of the top side of the bounding box.
   * @param right The x-coordinate of the right side of the bounding box.
   * @param bottom The y-coordinate of the bottom side of the bounding box.
   * @param frame The frame on which to draw the bounding box and label.
   */
  void drawPred(int classId, float conf, int left, int top, int right,
                int bottom, const cv::Mat& frame);

  /**
   * @brief Processes the output of the YOLO network and identifies detected
   * objects.
   * @param image The image/frame to be processed for detection.
   * @param output The network's output containing detection information.
   */
  void postprocess(const cv::Mat& image, const std::vector<cv::Mat>& output);

  /**
   * @brief Gets the class names for the detected objects.
   * @return A vector containing the class names.
   */
  const std::vector<std::string> get_className() const;

 private:
  cv::dnn::Net net; /**< YOLO network for object detection */
  /**< Vector of class names for detected objects */
  std::vector<std::string> classNames;
  float minConfidenceScore; /**< Min confidence score for detections */
  float nmsThreshold;       /**< NMS threshold for filtering detections */
};

}  // namespace Detector
