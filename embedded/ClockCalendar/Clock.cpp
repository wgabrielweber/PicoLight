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

void Clock::setClock(int hour, int minute, int second, bool is_pm) {
    if (hour >= 1 && hour <= 12) {
        time_.hour = hour;
        time_.is_pm = is_pm;
    } else {
        printf("Invalid hour input: %d\n", hour);
    }

    if (minute >= 0 && minute < 60) {
        time_.min = minute;
    } else {
        printf("Invalid minute input: %d\n", minute);
    }

    if (second >= 0 && second < 60) {
        time_.sec = second;
    } else {
        printf("Invalid second input: %d\n", second);
    }
}

void Clock::setClock(clock_time_t newTime) {
    time_ = newTime;
}

void Clock::readClock(int& hour, int& minute, int& second, bool& is_pm) {
    hour = time_.hour;
    minute = time_.min;
    second = time_.sec;
    is_pm = time_.is_pm;
}

void Clock::readClock(clock_time_t &currentTime) {
    currentTime = time_;
}

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