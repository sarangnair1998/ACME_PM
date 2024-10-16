#pragma once

/**
 * @file detector.hpp
 * @brief Header file for the Detector class.
 */

namespace Detector {
    /**
     * @class Detector
     * @brief Class for detecting humans using computer vision techniques.
     */
    class Detector {
    public:
        /**
         * @brief Constructor for Detector.
         */
        Detector();

        /**
         * @brief Destructor for Detector.
         */
        ~Detector();

        /**
         * @brief Method to initialize the detector.
         */
        void initialize();

        /**
         * @brief Method to detect humans.
         * @return An integer representing detection status.
         */
        int detect();
    };
}