#include <gtest/gtest.h>
#include "detector.hpp"
#include <opencv2/opencv.hpp>

using namespace Detector;
using namespace cv;
using namespace std;

// Test fixture for YOLODetector
class YOLODetectorTest : public ::testing::Test {
protected:
    unique_ptr<YOLODetector> detector;
    const string configPath = "config/yolov3.cfg";       
    const string weightsPath = "model/yolov3.weights"; 
    const string classesPath = "labels/coco.names"; 

    virtual void SetUp() override {
        // Instantiate YOLODetector object
        detector = make_unique<YOLODetector>(configPath, weightsPath, classesPath);
    }
};

// Test case for successful initialization
TEST_F(YOLODetectorTest, Initialization) {
    EXPECT_FALSE(detector->getNet().empty()) << "Network should be loaded successfully";
}

// Test for configuration loading failure
TEST(YOLODetectorExceptionTest, InitializationFailure) {
    // Attempt to initialize YOLODetector with invalid file paths
    EXPECT_THROW({
        YOLODetector detector("invalid.cfg", "invalid.weights", "invalid.names");
    }, runtime_error);
}

// Test for drawing predictions
TEST_F(YOLODetectorTest, DrawPrediction) {
    Mat frame(416, 416, CV_8UC3, Scalar(0, 0, 0));  // 3-channel black image
    int classId = 0;
    float confidence = 0.75;
    int left = 100, top = 50, right = 200, bottom = 150;

    detector->drawPred(classId, confidence, left, top, right, bottom, frame);

    // Convert frame to grayscale and validate drawing
    Mat grayFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    EXPECT_GT(countNonZero(grayFrame), 0) << "Frame should have non-zero pixels after drawing";
}

// Test post-processing with a simulated output
TEST_F(YOLODetectorTest, PostProcess) {
    Mat image(416, 416, CV_8UC3, Scalar(0, 0, 0));  // 3-channel black image
    vector<Mat> output(1, Mat::zeros(1, 85, CV_32F));  // Mocked output with one detection

    // Mocking the detection data with high confidence and person class
    output[0].at<float>(0, 4) = 1.0;         // Objectness score
    output[0].at<float>(0, 5) = 0.9;         // Class score
    output[0].at<float>(0, 0) = 0.5;         // Center x
    output[0].at<float>(0, 1) = 0.5;         // Center y
    output[0].at<float>(0, 2) = 0.1;         // Width
    output[0].at<float>(0, 3) = 0.1;         // Height

    detector->postprocess(image, output);

    // Convert image to grayscale and check for non-zero pixels
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);  // Convert to single channel
    EXPECT_GT(countNonZero(grayImage), 0) << "Image should have non-zero pixels after post-processing";
}


// Test for class names loading
TEST_F(YOLODetectorTest, LoadClassNames) {
    // Access classNames using the getter
    const vector<string>& classNames = detector->get_className();

    // Check that the class names vector is not empty
    EXPECT_FALSE(classNames.empty()) << "Class names should not be empty";
    
    // Check for specific class names if known
    EXPECT_EQ(classNames[0], "person") << "First class should be 'person'";
}

// Test confidence thresholding in post-processing
TEST_F(YOLODetectorTest, ConfidenceThresholding) {
    Mat image(416, 416, CV_8UC3, Scalar(0, 0, 0));  // 3-channel black image
    vector<Mat> output(1, Mat::zeros(1, 85, CV_32F));  // Mock output with low confidence

    // Set confidence below threshold
    output[0].at<float>(0, 4) = 0.3;

    detector->postprocess(image, output);

    // Convert image to grayscale and check for non-zero pixels
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    EXPECT_EQ(countNonZero(grayImage), 0) << "Low confidence detections should not draw on the image";
}

