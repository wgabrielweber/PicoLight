/**
 * @file Calendar.cpp
 * @brief Implementation of the Calendar class for managing dates.
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 12/11/2023
 * @institution UFSC
 */

#include "Calendar.hpp"

// Calendar class members
Calendar::Calendar() : date_{} {}

/**
 * @brief Constructor for the Calendar class with an initial date.
 * @param new_date The initial date.
 */
Calendar::Calendar(calendar_date_t new_date) : date_{new_date} {}

/**
 * @brief Set the date for the Calendar.
 * @param month The month.
 * @param day The day.
 * @param year The year.
 */
void Calendar::setCalendar(int month, int day, int year) {
    date_.month = month;
    date_.day = day;
    date_.year = year;
}

/**
 * @brief Set the date for the Calendar.
 * @param newDate The new date.
 */
void Calendar::setCalendar(calendar_date_t newDate) {
    // Similar validation can be added here
    date_ = newDate;
}

/**
 * @brief Read the current date from the Calendar.
 * @param month Reference to store the current month.
 * @param day Reference to store the current day.
 * @param year Reference to store the current year.
 */
void Calendar::readCalendar(int &month, int &day, int &year) {
    month = date_.month;
    day = date_.day;
    year = date_.year;
}

/**
 * @brief Read the current date from the Calendar.
 * @param readDate Reference to store the current date.
 */
void Calendar::readCalendar(calendar_date_t& readDate) {
    readDate = date_;
}

/**
 * @brief Advance the calendar by one day.
 */
void Calendar::advance() {
    date_.day++;
    if (date_.day > 30) {
        date_.day = 1;
        date_.month++;
        if (date_.month > 12) {
            date_.month = 1;
            date_.year++;
        }
    }
}