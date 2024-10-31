#include <gtest/gtest.h>
#include "detector.hpp"
#include <opencv2/opencv.hpp>



/**
 * @brief Test case for Detector initialization.
 */

using namespace Detector;
using namespace cv;
using namespace std;

// Test fixture for YOLODetector
class YOLODetectorTest : public ::testing::Test {
protected:
    unique_ptr<YOLODetector> detector;
    const string configPath = "../config/yolov3.cfg";       
    const string weightsPath = "../model/yolov3.weights"; 
    const string classesPath = "../labels/coco.names"; 

    // Absoulte path
    // const string configPath = "/home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/config/yolov3.cfg";       
    // const string weightsPath = "/home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/model/yolov3.weights"; 
    // const string classesPath = "/home/abhey/Desktop/Masters/Software_Dev/midterm/ACME_PM/labels/coco.names"; 

    virtual void SetUp() override {
        // Instantiate YOLODetector object
        detector = make_unique<YOLODetector>(configPath, weightsPath, classesPath);
    }
};

// Test case for successful initialization
TEST_F(YOLODetectorTest, Initialization) {
    EXPECT_FALSE(detector->getNet().empty())<< "Network should be loaded successfully";
}

// Test for configuration loading failure
TEST(YOLODetectorExceptionTest, InitializationFailure) {
    // Attempt to initialize YOLODetector with invalid file paths
    EXPECT_THROW({
        YOLODetector detector("invalid.cfg", "invalid.weights", "invalid.names");
    }, runtime_error);
}

// Test for drawing predictions with a boundary
TEST_F(YOLODetectorTest, DrawPredictionBoundary) {
    Mat frame(416, 416, CV_8UC3, Scalar(0, 0, 0)); // Initialize a black frame
    int classId = 0;
    float confidence = 0.75;
    int left = 100, top = 50, right = 200, bottom = 150;

    // Draw the prediction boundary on the frame
    detector->drawPred(classId, confidence, left, top, right, bottom, frame);

    // Convert frame to grayscale to use countNonZero safely
    Mat grayFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

    // Verify that drawing has modified the frame
    EXPECT_GT(countNonZero(grayFrame), 0) << "Frame should have non-zero pixels after drawing";
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

TEST_F(YOLODetectorTest, PostProcessValidDetection) {
    Mat frame(416, 416, CV_8UC3, Scalar(0, 0, 0)); // Dummy frame
    vector<Mat> dummyOutput(1, Mat(1, 85, CV_32F, Scalar(0))); // Dummy output matrix
    dummyOutput[0].at<float>(0, 0) = 0.5;  // Sample detection x
    dummyOutput[0].at<float>(0, 1) = 0.5;  // Sample detection y
    dummyOutput[0].at<float>(0, 2) = 0.5;  // Sample detection width
    dummyOutput[0].at<float>(0, 3) = 0.5;  // Sample detection height
    dummyOutput[0].at<float>(0, 5) = 0.9;  // Confidence

    EXPECT_NO_THROW(detector->postprocess(frame, dummyOutput));
}

TEST_F(YOLODetectorTest, DrawPredictionOutOfBounds) {
    Mat frame(416, 416, CV_8UC3, Scalar(0, 0, 0)); // Black frame
    int classId = 0;
    float confidence = 0.75;
    int left = -100, top = -50, right = 500, bottom = 500; // Out-of-bounds

    // Ensure no crash and appropriate handling
    EXPECT_NO_THROW(detector->drawPred(classId, confidence, left, top, right, bottom, frame));
}


// Test for video stream initialization
TEST_F(YOLODetectorTest, VideoStreamInitialization) {
    // Initialize video stream
    detector->videoStream(true);  // Run videoStream in test mode to limit frames
    // Optionally, you can add expectations here if you add output to videoStream in test mode
}

