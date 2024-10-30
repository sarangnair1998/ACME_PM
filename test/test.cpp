#include <gtest/gtest.h>
#include "detector.hpp"
#include <opencv2/opencv.hpp>

// #include "tracker.hpp"

/**
 * @brief Test case for Detector initialization.
 */
// TEST(DetectorTest, Initialization) {
//     Detector::Detector detector;
//     ASSERT_NO_THROW(detector.initialize());
// }

// /**
//  * @brief Test case for Detector detection.
//  */
// TEST(DetectorTest, Detection) {
//     Detector::Detector detector;
//     detector.initialize();
//     ASSERT_EQ(detector.detect(), 42);
// }

// /**
//  * @brief Test case for Tracker initialization.
//  */
// TEST(TrackerTest, Initialization) {
//     Tracker::Tracker tracker;
//     ASSERT_NO_THROW(tracker.initialize());
// }

// /**
//  * @brief Test case for Tracker tracking.
//  */
// TEST(TrackerTest, Tracking) {
//     // Create an instance of Tracker
//     Tracker::Tracker tracker;
//     tracker.initialize();

//     // Create a dummy measurement for tracking
//     cv::Point2f measurement(10.0f, 20.0f);

//     // Call track() with the measurement and check the result
//     ASSERT_EQ(tracker.track(measurement), 0);
//     // Assuming track returns 0 for success
// }

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


// // Test for drawing predictions
// TEST_F(YOLODetectorTest, DrawPrediction) {
//     Mat frame(416, 416, CV_8UC3, Scalar(0, 0, 0));
//     int classId = 0;
//     float confidence = 0.75;
//     int left = 100, top = 50, right = 200, bottom = 150;

//     detector->drawPred(classId, confidence, left, top, right, bottom, frame);

//     // Validate that drawing worked by checking if the frame is no longer all black
//     // bool drawingSuccessful = countNonZero(frame) > 0;
//     EXPECT_GT(countNonZero(frame), 0) << "No detections should result in no drawing on the image";
//     // EXPECT_TRUE(drawingSuccessful) << "Frame should have non-zero pixels after drawing";
// }


// // Test post-processing with a simulated output
// TEST_F(YOLODetectorTest, PostProcess) {
//     Mat image(416, 416, CV_8UC3, Scalar(0, 0, 0));
//     vector<Mat> output(1, Mat::zeros(1, 85, CV_32F));  // Mocked output, single detection with all zeros
//     output[0].at<float>(0, 4) = 1.0;  // Confidence score
//     output[0].at<float>(0, 5) = 0.8;  // Class score for person class (0)

//     // Mock data for bounding box positions
//     output[0].at<float>(0, 0) = 0.5;  // Center x
//     output[0].at<float>(0, 1) = 0.5;  // Center y
//     output[0].at<float>(0, 2) = 0.1;  // Width
//     output[0].at<float>(0, 3) = 0.1;  // Height

//     detector->postprocess(image, output);

//     EXPECT_GT(countNonZero(image), 0) << "Image should have non-zero pixels after post-processing";

//     // // Validate that post-processing worked by checking if the image is no longer all black
//     // bool postProcessingSuccessful = countNonZero(image) > 0;
//     // EXPECT_TRUE(postProcessingSuccessful) << "Image should have non-zero pixels after post-processing";
// }

// Test for class names loading
TEST_F(YOLODetectorTest, LoadClassNames) {
    // Access classNames using the getter
    const vector<string>& classNames = detector->get_className();

    // Check that the class names vector is not empty
    EXPECT_FALSE(classNames.empty()) << "Class names should not be empty";
    
    // Check for specific class names if known
    EXPECT_EQ(classNames[0], "person") << "First class should be 'person'";
}


// Test confidence thresholding
// TEST_F(YOLODetectorTest, ConfidenceThresholding) {
//     Mat image(416, 416, CV_8UC3, Scalar(0, 0, 0));
//     vector<Mat> output(1, Mat::zeros(1, 85, CV_32F));  // Mock output with no confidence

//     output[0].at<float>(0, 4) = 0.3;

//     detector->postprocess(image, output);

//     // Validate that no bounding box is drawn
//     EXPECT_EQ(countNonZero(image), 0) << "No detections should result in no drawing on the image";
// }






