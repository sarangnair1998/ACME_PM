#pragma once

/**
 * @file detector.hpp
 * @brief Header file for the ObjectDetector class using YOLOv3 for object detection.
 */

#include <cstddef>
#include <iostream>
#include <fstream>
#include <opencv2/core/types.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;
using namespace dnn;

namespace Detector {

    class YOLODetector {
        
        public:
            // constructor
            YOLODetector(const string& configPath, const string& weightsPath, const string& classesPath);
            //Initialize video capture 
            void videoStream();
            // getter for net
            const Net& getNet() const;

            void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);

            void postprocess(Mat& image, const vector<Mat>& output);

            const vector<string> get_className() const;

        private:

            Net net;
            vector<string> classNames;
            float minConfidenceScore;
            float nmsThreshold;
    };

}  // namespace Detector


