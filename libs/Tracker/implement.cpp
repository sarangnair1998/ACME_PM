#include "tracker.hpp"

namespace Tracker {

/**
 * @brief Construct a new Tracker::Tracker object.
 * Initializes the Kalman filter and other necessary matrices.
 */
Tracker::Tracker()
    : kf(4, 2, 0),  // Kalman Filter with 4 state variables (x, y, dx, dy)
                    // and 2 measurements (x, y)
      state(4, 1, CV_32F),
      measurement(2, 1, CV_32F),
      isInitialized(false) {
    // Initialize Kalman filter matrices
    kf.transitionMatrix = (cv::Mat_<float>(4, 4) << 1, 0, 1, 0,
                                                    0, 1, 0, 1,
                                                    0, 0, 1, 0,
                                                    0, 0, 0, 1);

    kf.measurementMatrix = (cv::Mat_<float>(2, 4) << 1, 0, 0, 0,
                                                     0, 1, 0, 0);

    cv::setIdentity(kf.processNoiseCov,
     cv::Scalar::all(1e-2));  // Process noise covariance
    cv::setIdentity(kf.measurementNoiseCov,
     cv::Scalar::all(1e-1));  // Measurement noise covariance
    cv::setIdentity(kf.errorCovPost,
     cv::Scalar::all(1));  // Error covariance

    state.setTo(cv::Scalar(0));
    measurement.setTo(cv::Scalar(0));
}

/**
 * @brief Destroy the Tracker::Tracker object.
 * Cleans up resources allocated for the tracker.
 */
Tracker::~Tracker() {
    // Destructor implementation
}

/**
 * @brief Initialize the tracker with default values.
 * Sets the initial state and flags the tracker as initialized.
 */
void Tracker::initialize() {
    // Set initial state
    state.setTo(cv::Scalar(0));
    isInitialized = true;
}

/**
 * @brief Tracks the target based on the given measurement.
 * This method uses the Kalman filter to predict and correct the state of the target.
 *
 * @param meas The observed position of the target.
 * @return int Status of the tracking operation (0 for success).
 */
int Tracker::track(const cv::Point2f& meas) {
    if (!isInitialized) {
        initialize();
        // Set initial state to the measurement
        state.at<float>(0) = meas.x;
        state.at<float>(1) = meas.y;
        kf.statePost = state;
    }

    // Prediction step
    cv::Mat prediction = kf.predict();
    cv::Point2f predictPt(prediction.at<float>(0), prediction.at<float>(1));

    // Correction step with measurement update
    measurement.at<float>(0) = meas.x;
    measurement.at<float>(1) = meas.y;
    kf.correct(measurement);

    return 0;
    // Return success status
    // (could be modified based on requirements)
}

/**
 * @brief Get the predicted position of the target.
 * Uses the Kalman filter to predict the next position of the tracked target.
 *
 * @return cv::Point2f The predicted position of the target.
 */
cv::Point2f Tracker::getPredictedPosition() {
    cv::Mat prediction = kf.predict();
    return cv::Point2f(prediction.at<float>(0), prediction.at<float>(1));
}

}  // namespace Tracker
