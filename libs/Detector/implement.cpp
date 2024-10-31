// Copyright [2024] Abhey Sharma, Prathinav K V, Sarang Nair

#include "detector.hpp"

namespace Detector {

/**
 * @brief Constructs a YOLODetector object, loads the YOLO model and class
 * names.
 * @param configPath Path to the YOLO configuration file.
 * @param weightsPath Path to the YOLO weights file.
 * @param classesPath Path to the file containing class names.
 */
YOLODetector::YOLODetector(const std::string& configPath,
                           const std::string& weightsPath,
                           const std::string& classesPath)
    : minConfidenceScore(0.5), nmsThreshold(0.4) {
  // Load model
  try {
    net = cv::dnn::readNetFromDarknet(configPath, weightsPath);
  } catch (const cv::Exception& e) {
    std::cerr << "Error loading network: " << e.what() << std::endl;
    throw std::runtime_error("Failed to initialize YOLODetector: " +
                             std::string(e.what()));
  }

  if (net.empty()) {
    std::cerr << "Failed to load network!" << std::endl;
    throw std::runtime_error("Failed to load network");
  }

  // Load class names from file
  std::ifstream ifs(classesPath.c_str());
  std::string line;
  while (std::getline(ifs, line)) {
    if (!line.empty()) {  // Avoid adding empty lines
      classNames.push_back(line);
    }
  }

  if (classNames.empty()) {
    std::cerr << "Failed to load class names!" << std::endl;
    throw std::runtime_error("Failed to load class names");
  }
}

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
void YOLODetector::drawPred(int classId, float conf, int left, int top,
                            int right, int bottom, const cv::Mat& frame) {
  cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom),
                cv::Scalar(255, 178, 50), 3);

  std::string label = cv::format("%.2f", conf);
  if (!classNames.empty() && classId < static_cast<int>(classNames.size())) {
    label = classNames[classId] + ":" + label;
  }

  int baseLine;
  cv::Size labelSize =
      cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
  top = std::max(top, labelSize.height);
  cv::rectangle(
      frame, cv::Point(left, top - cvRound(1.5 * labelSize.height)),
      cv::Point(left + cvRound(1.5 * labelSize.width), top + baseLine),
      cv::Scalar(255, 255, 255), cv::FILLED);
  cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX,
              0.75, cv::Scalar(0, 0, 0), 1);
}

/**
 * @brief Processes the output of the YOLO network and identifies detected
 * objects.
 * @param image The image/frame to be processed for detection.
 * @param output The network's output containing detection information.
 */
void YOLODetector::postprocess(const cv::Mat& image,
                               const std::vector<cv::Mat>& output) {
  int personClassId = 0;
  std::vector<int> classIds;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;

  for (size_t i = 0; i < output.size(); ++i) {
    auto* data = reinterpret_cast<float*>(output[i].data);

    for (int j = 0; j < output[i].rows; ++j, data += output[i].cols) {
      cv::Mat scores = output[i].row(j).colRange(5, output[i].cols);
      cv::Point classIdPoint;
      double confidence;

      cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
      if (confidence > minConfidenceScore && classIdPoint.x == personClassId) {
        int centerX = static_cast<int>(data[0] * image.cols);
        int centerY = static_cast<int>(data[1] * image.rows);
        int width = static_cast<int>(data[2] * image.cols);
        int height = static_cast<int>(data[3] * image.rows);
        int left = centerX - width / 2;
        int top = centerY - height / 2;

        classIds.push_back(classIdPoint.x);
        confidences.push_back(static_cast<float>(confidence));
        boxes.push_back(cv::Rect(left, top, width, height));
      }
    }
  }

  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, confidences, minConfidenceScore, nmsThreshold,
                    indices);
  for (size_t i = 0; i < indices.size(); ++i) {
    int idx = indices[i];
    cv::Rect box = boxes[idx];
    drawPred(classIds[idx], confidences[idx], box.x, box.y, box.x + box.width,
             box.y + box.height, image);
  }
}

/**
 * @brief Starts the video stream for object detection.
 * @param testMode If true, enables test mode for the video stream.
 */
void YOLODetector::videoStream(bool testMode) {
  std::vector<std::string> outputLayerNames =
      net.getUnconnectedOutLayersNames();

  cv::VideoCapture cap(0);
  if (!cap.isOpened()) {
    std::cerr << "Error opening video stream or file" << std::endl;
    return;
  }

  int frameCount = 0;

  while (cap.isOpened()) {
    cv::Mat image;
    bool isSuccess = cap.read(image);
    if (!isSuccess) {
      std::cerr << "Failed to load frame!" << std::endl;
      break;
    }

    cv::Mat blob = cv::dnn::blobFromImage(image, 1 / 255.0, cv::Size(416, 416),
                                          cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);

    std::vector<cv::Mat> output;
    net.forward(output, outputLayerNames);

    postprocess(image, output);
    cv::imshow("YOLO Detection", image);

    frameCount++;
    if (testMode && frameCount >= 1) {  // Exit after one frame in test mode
      break;
    }

    int k = cv::waitKey(10);
    if (k == 113) {  // Press 'q' to exit
      break;
    }
  }

  cap.release();
  cv::destroyAllWindows();
}

/**
 * @brief Gets the YOLO network object.
 * @return A constant reference to the cv::dnn::Net object.
 */
const cv::dnn::Net& YOLODetector::getNet() const { return net; }

/**
 * @brief Gets the class names for the detected objects.
 * @return A vector containing the class names.
 */
const std::vector<std::string> YOLODetector::get_className() const {
  return classNames;
}

}  // namespace Detector
