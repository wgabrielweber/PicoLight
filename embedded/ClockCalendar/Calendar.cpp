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

Calendar::Calendar(calendar_date_t new_date) : date_{new_date} {}

void Calendar::setCalendar(int month, int day, int year) {
    date_.month = month;
    date_.day = day;
    date_.year = year;
}

void Calendar::setCalendar(calendar_date_t newDate) {
    date_ = newDate;
}

void Calendar::readCalendar(int &month, int &day, int &year) {
    month = date_.month;
    day = date_.day;
    year = date_.year;
}

void Calendar::readCalendar(calendar_date_t& readDate) {
    readDate = date_;
}

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