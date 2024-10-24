#include <iostream>
#include "detector.hpp"
#include "tracker.hpp"

int main() {
    // Create instances of Detector and Tracker

    Detector::ObjectDetector detector;
    Tracker::Tracker tracker;

    // Initialize components
    detector.initialize();
    tracker.initialize();

    // Perform detection
    detector.start();
    
    // Create a dummy measurement for tracking
    cv::Point2f measurement(10.0f, 20.0f);  // Example measurement values

    // Perform tracking
    int trackingResult = tracker.track(measurement);
    std::cout << "Tracking Initialized value:" << trackingResult << std::endl;

    return 0;
}
