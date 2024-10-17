#pragma once

/**
 * @file tracker.hpp
 * @brief Header file for the Tracker class.
 */

namespace Tracker {
    /**
     * @class Tracker
     * @brief Class for tracking humans using computer vision techniques.
     */
    class Tracker {
    public:
        /**
         * @brief Constructor for Tracker.
         */
        Tracker();

        /**
         * @brief Destructor for Tracker.
         */
        ~Tracker();

        /**
         * @brief Method to initialize the tracker.
         */
        void initialize();

        /**
         * @brief Method to track humans.
         * @return An integer representing tracking status.
         */
        int track();
    };
}
