/**
 * @file ClockCalendar.cpp
 * @brief Implementation of the ClockCalendar class for managing times and dates.
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 12/11/2023
 * @institution UFSC
 */

#include "ClockCalendar.hpp"
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

// ClockCalendar class members

/**
 * @brief Default constructor for the ClockCalendar class.
 */
ClockCalendar::ClockCalendar(bool rtc_initializer) : Clock(), Calendar() {
    if (rtc_initializer) {
        datetime_t rtc_time;

        // Get the current date and time from the RTC
        if (rtc_get_datetime(&rtc_time)) {
            int month = rtc_time.month;
            int day = rtc_time.day;
            int year = rtc_time.year;
            int hour = rtc_time.hour;
            int minute = rtc_time.min;
            int second = rtc_time.sec;

            // Changes from 24h format to 12h format
            bool is_pm = false;
            if (hour >= 12) {
                is_pm = true;
                if (hour >= 13) {
                    hour -= 12;
                }
            } else {
                is_pm = false;
            }

            // Stores the adjusted time information
            Clock::setClock(hour, minute, second, is_pm);
            Calendar::setCalendar(month, day, year);
        } else {
            // Handle the case when getting RTC data fails
            setCustomTimeAndDate(1, 1, 2023, 10, 30, 0, false); // Set a default time and date
        }
    }
}

void ClockCalendar::setCustomTimeAndDate(int month, int day, int year, int hour, int minute, int second, bool is_pm) {
    // Set the personalized time and date
    Clock::setClock(hour, minute, second, is_pm);
    Calendar::setCalendar(month, day, year);
}


/**
 * @brief Constructor for the ClockCalendar class with specific values.
 * 
 * @param month Month.
 * @param day Day.
 * @param year Year.
 * @param hour Hour.
 * @param minute Minutes.
 * @param second Seconds.
 * @param is_pm am:pm indicator.
 * @param rtc_initializer Flag to initialize from RTC.
 */
ClockCalendar::ClockCalendar(int month, int day, int year, int hour, int minute, int second, bool is_pm, bool rtc_initializer)
    : Clock(clock_time_t{static_cast<int8_t>(hour), static_cast<int8_t>(minute), static_cast<int8_t>(second), is_pm}),
      Calendar(calendar_date_t{static_cast<int16_t>(month), static_cast<int8_t>(day), static_cast<int8_t>(year)}) {
    if (rtc_initializer) {
        // Additional initialization from RTC if needed
    }
}

/**
 * @brief Constructor for the ClockCalendar class with clock_time_t and calendar_date_t structs.
 * 
 * @param new_time New time to set.
 * @param new_date New date to set.
 * @param rtc_initializer Flag to initialize from RTC.
 */
ClockCalendar::ClockCalendar(clock_time_t new_time, calendar_date_t new_date, bool rtc_initializer)
    : Clock(new_time), Calendar(new_date) {
    if (rtc_initializer) {
        // Additional initialization from RTC if needed
    }
}

/**
 * @brief Advances the clock by one second.
 */
void ClockCalendar::advance()
{
    // First, advance the time
    Clock::advance();

    // Check if the time change affected the date (AM to PM or vice versa)
    bool was_pm = time_.is_pm;
    if ((was_pm) && (!time_.is_pm))
    {
        // If so, advance the calendar
        Calendar::advance();
    }
}