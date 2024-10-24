#pragma once

/**
 * @file detector.hpp
 * @brief Header file for the ObjectDetector class using YOLOv3 for object detection.
 */

#include <opencv2/core/types.hpp>
#include <opencv2/dnn.hpp>
#include <string>
#include <vector>

namespace Detector {
    /**
     * @class ObjectDetector
     * @brief Class for real-time object detection using YOLOv3 neural network.
     */
    class ObjectDetector {
    public:
        /**
         * @brief Constructor for ObjectDetector.
         * @param model_path Path to YOLOv3 weights file
         * @param config_path Path to YOLOv3 configuration file
         * @param labels_path Path to class labels file
         * @param confidence_threshold Minimum confidence score for detections
         */
        ObjectDetector(
            const std::string& model_path = "./model/yolov3.weights",
            const std::string& config_path = "./config/yolov3.cfg",
            const std::string& labels_path = "/labels/coco.names",
            float confidence_threshold = 0.5
        );

        /**
         * @brief Destructor for ObjectDetector.
         */
        ~ObjectDetector();

        /**
         * @brief Initialize the detector by loading model and class names.
         * @return True if initialization successful, false otherwise.
         */
        bool initialize();

        /**
         * @brief Start real-time object detection using webcam.
         */
        void start();

        /**
         * @brief Process a single frame for object detection.
         * @param frame Input frame to process
         */
        void processFrame(cv::Mat& frame);

    private:
        /**
         * @brief Load class names from file.
         * @return True if loading successful, false otherwise.
         */
        bool loadClassNames();

        /**
         * @brief Load neural network model.
         * @return True if loading successful, false otherwise.
         */
        bool loadNetwork();

        /**
         * @brief Preprocess frame for neural network input.
         * @param frame Input frame to preprocess
         * @return Preprocessed blob
         */
        cv::Mat preprocess(const cv::Mat& frame);

        /**
         * @brief Draw detection results on frame.
         * @param frame Frame to draw on
         * @param results Detection results
         */
        void drawPredictions(cv::Mat& frame, const cv::Mat& results);

        std::string model_path_;    ///< Path to YOLOv3 weights
        std::string config_path_;   ///< Path to YOLOv3 config
        std::string labels_path_;   ///< Path to class labels
        float min_confidence_score_; ///< Minimum confidence threshold
        std::vector<std::string> class_names_; ///< Vector of class labels
        cv::dnn::Net net_;         ///< Neural network object
    };
}  // namespace Detector