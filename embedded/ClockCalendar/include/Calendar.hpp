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

typedef struct {
    int16_t year; 
    int8_t month; 
    int8_t day;   
} calendar_date_t;

class Calendar {
protected:
    calendar_date_t date_; /**< Current date. */

public:

    Calendar();

    Calendar(calendar_date_t date);

    void setCalendar(int month, int day, int year);

    void setCalendar(calendar_date_t newDate);

    void readCalendar(int& month, int& day, int& year);

    void readCalendar(calendar_date_t& readDate);

    void advance();
};

#endif /* CALENDAR_HPP_ */