// Copyright [2024] Abhey Sharma, Prathinav K V, Sarang Nair

/**
 * @file test.cpp
 * @brief Unit tests for the YOLODetector class using Google Test framework.
 *
 * This file contains test cases to verify the functionality of the YOLODetector
 * class. The tests cover initialization, loading of class names, drawing
 * prediction boundaries, valid detection post-processing, and video stream
 * initialization.
 */

#include <gtest/gtest.h>

#include <opencv2/opencv.hpp>

#include "detector.hpp"

/**
 * @namespace Detector
 * @brief Namespace containing the YOLODetector class and associated functions.
 */
using cv::Mat;
using cv::Scalar;
using Detector::YOLODetector;

/**
 * @class YOLODetectorTest
 * @brief Google Test fixture class for testing YOLODetector.
 *
 * This class contains setup and helper functions for initializing YOLODetector
 * instances, as well as file paths for configuration, weights, and class names.
 */
class YOLODetectorTest : public ::testing::Test {
 protected:
  /**< Unique pointer to YOLODetector instance */
  std::unique_ptr<YOLODetector> detector;
  /**< Path to YOLO config file */
  const std::string configPath = "config/yolov3.cfg";
  /**< Path to YOLO weights file */
  const std::string weightsPath = "model/yolov3.weights";
  /**< Path to labels file */
  const std::string classesPath = "labels/coco.names";

  /**
   * @brief Sets up a new YOLODetector instance for each test case.
   */
  void SetUp() override {
    detector =
        std::make_unique<YOLODetector>(configPath, weightsPath, classesPath);
  }
};

/**
 * @brief Test case for successful initialization of YOLODetector.
 *
 * Verifies that the YOLO network is loaded correctly.
 */
TEST_F(YOLODetectorTest, Initialization) {
  EXPECT_FALSE(detector->getNet().empty())
      << "Network should be loaded successfully";
}

/**
 * @brief Test case for initialization failure of YOLODetector.
 *
 * Attempts to initialize YOLODetector with invalid paths to verify exception
 * handling.
 */
TEST(YOLODetectorExceptionTest, InitializationFailure) {
  EXPECT_THROW(
      {
        YOLODetector detector("invalid.cfg", "invalid.weights",
                              "invalid.names");
      },
      std::runtime_error);
}

/**
 * @brief Test case for drawing predictions with boundary checking.
 *
 * Tests if drawing predictions modifies the frame as expected.
 */
TEST_F(YOLODetectorTest, DrawPredictionBoundary) {
  Mat frame(416, 416, CV_8UC3, Scalar(0, 0, 0));  // Initialize a black frame
  int classId = 0;
  float confidence = 0.75;
  int left = 100, top = 50, right = 200, bottom = 150;

  // Draw the prediction boundary on the frame
  detector->drawPred(classId, confidence, left, top, right, bottom, frame);

  Mat grayFrame;
  cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

  EXPECT_GT(cv::countNonZero(grayFrame), 0)
      << "Frame should have non-zero pixels after drawing";
}

/**
 * @brief Test case for loading class names in YOLODetector.
 *
 * Verifies that class names are loaded successfully and checks the first class
 * name.
 */
TEST_F(YOLODetectorTest, LoadClassNames) {
  const std::vector<std::string>& classNames = detector->get_className();

  EXPECT_FALSE(classNames.empty()) << "Class names should not be empty";
  EXPECT_EQ(classNames[0], "person") << "First class should be 'person'";
}

/**
 * @brief Test case for post-processing of valid detections.
 *
 * Tests if post-processing with a valid detection data does not throw an
 * exception.
 */
TEST_F(YOLODetectorTest, PostProcessValidDetection) {
  Mat frame(416, 416, CV_8UC3, Scalar(0, 0, 0));  // Dummy frame
  std::vector<Mat> dummyOutput(
      1, Mat(1, 85, CV_32F, Scalar(0)));  // Dummy output matrix

  dummyOutput[0].at<float>(0, 0) = 0.5f;
  dummyOutput[0].at<float>(0, 1) = 0.5f;
  dummyOutput[0].at<float>(0, 2) = 0.5f;
  dummyOutput[0].at<float>(0, 3) = 0.5f;
  dummyOutput[0].at<float>(0, 5) = 0.9f;  // Confidence

  EXPECT_NO_THROW(detector->postprocess(frame, dummyOutput));
}

/**
 * @brief Test case for drawing predictions with out-of-bounds coordinates.
 *
 * Tests if drawing predictions with out-of-bounds coordinates does not throw an
 * exception.
 */
TEST_F(YOLODetectorTest, DrawPredictionOutOfBounds) {
  Mat frame(416, 416, CV_8UC3, Scalar(0, 0, 0));  // Black frame
  int classId = 0;
  float confidence = 0.75f;
  int left = -100, top = -50, right = 500, bottom = 500;  // Out-of-bounds

  EXPECT_NO_THROW(
      detector->drawPred(classId, confidence, left, top, right, bottom, frame));
}

/**
 * @brief Test case for video stream initialization.
 *
 * Runs the videoStream method in test mode to verify initialization.
 */
TEST_F(YOLODetectorTest, VideoStreamInitialization) {
  detector->videoStream(true);  // Run videoStream in test mode to limit frames
}
