/**
 * @file Clock.hpp
 * @brief Definition of the Clock class for managing time.
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 12/11/2023
 * @institution UFSC
 */

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <stdint.h>
#include <stdio.h>

/**
 * @struct clock_time_t
 * @brief Structure to represent the time.
 */
typedef struct {
    int8_t hour; /**< Hours. */
    int8_t min;  /**< Minutes. */
    int8_t sec;  /**< Seconds. */
    bool is_pm;  /**< AM/PM indicator. */
} clock_time_t;

/**
 * @class Clock
 * @brief Class for managing time.
 */
class Clock {
protected:
    clock_time_t time_; /**< Current time. */

public:
    /**
     * @brief Default constructor for the Clock class.
     */
    Clock();

    /**
     * @brief Constructor for the Clock class with initial time.
     * @param initialTime The initial time.
     */
    Clock(clock_time_t initialTime);

    /**
     * @brief Set the time for the Clock.
     * @param newTime The new time.
     */
    void setClock(int hour, int minute, int second, bool is_pm);
    void setClock(clock_time_t newTime);

    /**
     * @brief Read the current time from the Clock.
     * @param currentTime Reference to store the current time.
     */
    void readClock(int& hour, int& minute, int& second, bool& is_pm);
    void readClock(clock_time_t& currentTime);

    /**
     * @brief Advance the clock by one second.
     */
    void advance();
};

#endif /* CLOCK_HPP_ */
