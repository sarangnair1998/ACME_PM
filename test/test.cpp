#include <gtest/gtest.h>

#include "lib1.hpp"

// Test case for checking the PID controller's compute_speed function
TEST(PidControllerTest, DecreasedSpeedTest) {
  // Initialize a PidController with a desired speed of 50
  PidController pid(50.0);

  // // Get the initial actual speed
  double initial_speed = pid.get_actual_speed();

  // Call compute_speed() multiple times and check if speed is moving toward the
  // desired speed
  double computed_speed = pid.compute_speed();

  // After one computation, speed should decrease (since the desired speed is
  // 50, which is less than 100)
  EXPECT_LT(computed_speed, initial_speed);  // Expect computed speed to be less
                                             // than the initial speed
}
// Test case for checking the PID controller's compute_speed function
TEST(PidControllerTest, IncreasedSpeedTest) {
  // Initialize a PidController with a desired speed of 150
  PidController pid(150.0);

  // // Get the initial actual speed
  double initial_speed = pid.get_actual_speed();

  // Call compute_speed() multiple times and check if speed is moving toward the
  // desired speed
  double computed_speed = pid.compute_speed();

  // After one computation, speed should increase (since the desired speed is
  // 150, which is more than 100)
  EXPECT_GT(computed_speed, initial_speed);  // Expect computed speed to be less
                                             // than the initial speed
}
