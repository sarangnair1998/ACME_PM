#include "detector.hpp"
#include "tracker.hpp"
#include <iostream>

int main() {
    // Create instances of Detector and Tracker
    Detector::Detector detector;
    Tracker::Tracker tracker;

    // Initialize components
    detector.initialize();
    tracker.initialize();

    // Perform detection
    int detectionResult = detector.detect();
    std::cout << "Detection Initalized and value is: " << detectionResult << std::endl;

    // Perform tracking
    int trackingResult = tracker.track();
    std::cout << "Tracking Initialized and value is: " << trackingResult << std::endl;

    return 0;
}
