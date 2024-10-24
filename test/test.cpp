#include <gtest/gtest.h>
#include "detector.hpp"
#include "tracker.hpp"

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

/**
 * @brief Test case for Tracker initialization.
 */
TEST(TrackerTest, Initialization) {
    Tracker::Tracker tracker;
    ASSERT_NO_THROW(tracker.initialize());
}

/**
 * @brief Test case for Tracker tracking.
 */
TEST(TrackerTest, Tracking) {
    // Create an instance of Tracker
    Tracker::Tracker tracker;
    tracker.initialize();

    // Create a dummy measurement for tracking
    cv::Point2f measurement(10.0f, 20.0f);

    // Call track() with the measurement and check the result
    ASSERT_EQ(tracker.track(measurement), 0);
    // Assuming track returns 0 for success
}
