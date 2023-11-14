/**
 * @file Clock.cpp
 * @brief Implementation of the Clock class for managing time.
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 12/11/2023
 * @institution UFSC
 */

#include "Clock.hpp"

// Clock class members
Clock::Clock() : time_{} {}

Clock::Clock(clock_time_t new_time) : time_{new_time} {}

/**
 * @brief Set the time for the Clock.
 * @param hour Hours.
 * @param minute Minutes.
 * @param second Seconds.
 * @param is_pm AM/PM indicator.
 */
void Clock::setClock(int hour, int minute, int second, bool is_pm) {
    if (hour >= 1 && hour <= 12) {
        time_.hour = hour;
        time_.is_pm = is_pm;
    } else {
        // Handle invalid hour input, perhaps throw an exception or set to a default value
        printf("Invalid hour input: %d\n", hour);
    }

    if (minute >= 0 && minute < 60) {
        time_.min = minute;
    } else {
        // Handle invalid minute input
        printf("Invalid minute input: %d\n", minute);
    }

    if (second >= 0 && second < 60) {
        time_.sec = second;
    } else {
        // Handle invalid second input
        printf("Invalid second input: %d\n", second);
    }
}

/**
 * @brief Set the time for the Clock.
 * @param newTime The new time.
 */
void Clock::setClock(clock_time_t newTime) {
    // Similar validation can be added here
    time_ = newTime;
}

/**
 * @brief Read the current time from the Clock.
 * @param hour Hours.
 * @param minute Minutes.
 * @param second Seconds.
 * @param is_pm AM/PM indicator.
 */
void Clock::readClock(int& hour, int& minute, int& second, bool& is_pm) {
    hour = time_.hour;
    minute = time_.min;
    second = time_.sec;
    is_pm = time_.is_pm;
}

/**
 * @brief Read the current time from the Clock.
 * @param currentTime Reference to store the current time structure.
 */
void Clock::readClock(clock_time_t &currentTime) {
    currentTime = time_;
}

/**
 * @brief Advance the clock by one second.
 */
void Clock::advance() {
    time_.sec++;
    if (time_.sec >= 60) {
        time_.sec = 0;
        time_.min++;
        if (time_.min >= 60) {
            time_.min = 0;
            time_.hour++;
            if (time_.hour >= 13) {
                time_.hour = 1;
            }

            // Toggle AM/PM
            time_.is_pm = !time_.is_pm;
        }
    }
}