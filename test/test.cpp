#include "detector.hpp"
#include "tracker.hpp"
#include <gtest/gtest.h>

/**
 * @brief Test case for Detector initialization.
 */
TEST(DetectorTest, Initialization) {
    Detector::Detector detector;
    ASSERT_NO_THROW(detector.initialize());
}

/**
 * @brief Test case for Detector detection.
 */
TEST(DetectorTest, Detection) {
    Detector::Detector detector;
    detector.initialize();
    ASSERT_EQ(detector.detect(), 42);
}

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
    Tracker::Tracker tracker;
    tracker.initialize();
    ASSERT_EQ(tracker.track(), 7);
}