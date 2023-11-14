/**
 * @file Calendar.hpp
 * @brief Definition of the Calendar class for managing dates.
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 12/11/2023
 * @institution UFSC
 */

#ifndef CALENDAR_HPP_
#define CALENDAR_HPP_

#include <stdint.h>
#include <stdio.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

/**
 * @struct calendar_date_t
 * @brief Structure to represent a date.
 */
typedef struct {
    int16_t year; /**< Year. */
    int8_t month; /**< Month. */
    int8_t day;   /**< Day. */
} calendar_date_t;

/**
 * @class Calendar
 * @brief Class for managing dates.
 */
class Calendar {
protected:
    calendar_date_t date_; /**< Current date. */

public:
    /**
     * @brief Default constructor for the Calendar class.
     */
    Calendar();

    /**
     * @brief Constructor for the Calendar class with an initial date.
     * @param date The initial date.
     */
    Calendar(calendar_date_t date);

    /**
     * @brief Set the date for the Calendar.
     * @param month The month.
     * @param day The day.
     * @param year The year.
     */
    void setCalendar(int month, int day, int year);

    /**
     * @brief Set the date for the Calendar.
     * @param newDate The new date.
     */
    void setCalendar(calendar_date_t newDate);

    /**
     * @brief Read the current date from the Calendar.
     * @param month Reference to store the current month.
     * @param day Reference to store the current day.
     * @param year Reference to store the current year.
     */
    void readCalendar(int& month, int& day, int& year);

    /**
     * @brief Read the current date from the Calendar.
     * @param readDate Reference to store the current date.
     */
    void readCalendar(calendar_date_t& readDate);

    /**
     * @brief Advance the calendar by one day.
     */
    void advance();
};

#endif /* CALENDAR_HPP_ */