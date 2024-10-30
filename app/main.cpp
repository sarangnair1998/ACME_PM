#include <iostream>
#include "detector.hpp"
#include "tracker.hpp"

// int main() {
//     // Create instances of Detector and Tracker
//     Detector::Detector detector;
//     Tracker::Tracker tracker;

//     // Initialize components
//     detector.initialize();
//     tracker.initialize();

//     // Perform detection
//     int detectionResult = detector.detect();
//     std::cout << "Detection Initalized value:" <<  detectionResult << std::endl;

//     // Create a dummy measurement for tracking
//     cv::Point2f measurement(10.0f, 20.0f);  // Example measurement values

//     // Perform tracking
//     int trackingResult = tracker.track(measurement);
//     std::cout << "Tracking Initialized value:" << trackingResult << std::endl;

//     return 0;
// }

int main()
{
    try {
        Detector::YOLODetector detector("./config/yolov3.cfg", "./model/yolov3.weights", "./labels/coco.names");
        // Detector::YOLODetector detector("./config/yolov3.cfg", "./model/yolov3.weights", "./labels/coco.names");
        detector.videoStream();
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return -1;
    }

    return 0;
}

