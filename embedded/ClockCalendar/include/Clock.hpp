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

typedef struct {
    int8_t hour; /**< Hours. */
    int8_t min;  /**< Minutes. */
    int8_t sec;  /**< Seconds. */
    bool is_pm;  /**< AM/PM indicator. */
} clock_time_t;

class Clock {
protected:
    clock_time_t time_; /**< Current time. */

public:

    Clock();

    Clock(clock_time_t initialTime);

    void setClock(int hour, int minute, int second, bool is_pm);
    void setClock(clock_time_t newTime);

    void readClock(int& hour, int& minute, int& second, bool& is_pm);
    void readClock(clock_time_t& currentTime);

    void advance();
};

#endif /* CLOCK_HPP_ */
