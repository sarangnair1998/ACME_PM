#include <gtest/gtest.h>

/**
 * @brief Main function to run all tests.
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}