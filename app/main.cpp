#include <iostream>
#include "detector.hpp"

int main()
{
    string configPath = "./config/yolov3.cfg";
    string weightsPath = "./model/yolov3.weights";
    string labelsPath = "./labels/coco.names";

    // Check if configuration file exists
    ifstream configFile(configPath);
    if (!configFile.good()) {
        cerr << "Error: Configuration file not found at " << configPath << endl;
        return -1;
    }

    // Check if weights file exists
    ifstream weightsFile(weightsPath);
    if (!weightsFile.good()) {
        cerr << "Error: Weights file not found at " << weightsPath << endl;
        return -1;
    }

    // Check if labels file exists
    ifstream labelsFile(labelsPath);
    if (!labelsFile.good()) {
        cerr << "Error: Labels file not found at " << labelsPath << endl;
        return -1;
    }

    try {
        Detector::YOLODetector detector(configPath, weightsPath, labelsPath);
        detector.videoStream();
        
    } catch (const cv::Exception& e) {
        cerr << "OpenCV Error: " << e.what() << endl;
        return -1;
    } catch (const runtime_error& e) {
        cerr << "Runtime Error: " << e.what() << endl;
        return -1;
    }

    return 0;
}