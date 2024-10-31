// Copyright [2024] Abhey Sharma, Prathinav K V, Sarang Nair
#pragma once

#include <opencv2/core.hpp>
#include <opencv2/video/tracking.hpp>  // Added for KalmanFilter

/**
 * @file tracker.hpp
 * @brief Header file for the Tracker class.
 */

namespace Tracker {

/**
 * @class Tracker
 * @brief Class for tracking humans using computer vision techniques.
 */
class Tracker {
 public:
  /**
   * @brief Constructor for Tracker.
   */
  Tracker();

  /**
   * @brief Destructor for Tracker.
   */
  ~Tracker();

  /**
   * @brief Method to initialize the tracker.
   */
  void initialize();

  /**
   * @brief Method to track humans.
   * @param measurement - the observed position of the target.
   * @return An integer representing tracking status.
   */
  int track(const cv::Point2f& measurement);

  /**
   * @brief Get the predicted position.
   * @return Predicted position of the target.
   */
  cv::Point2f getPredictedPosition();

 private:
  cv::KalmanFilter kf;  // Kalman filter for tracking
  cv::Mat state;        // State matrix [x, y, dx, dy]
  cv::Mat measurement;  // Measurement matrix [x, y]
  bool isInitialized;   // Tracker initialization flag
};

}  // namespace Tracker
