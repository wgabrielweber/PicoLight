/**
 * @file ClockCalendar.hpp
 * @brief Definition of the ClockCalendar class for managing both time and date.
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 12/11/2023
 * @institution UFSC
 */

#ifndef CLK_CAL_HPP_
#define CLK_CAL_HPP_

#include "Clock.hpp"
#include "Calendar.hpp"
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

class ClockCalendar : public Clock, public Calendar {
public:

    ClockCalendar(bool rtc_initializer);

    ClockCalendar(int month, int day, int year, int hour, int minute, int second, bool is_pm, bool rtc_initializer);

    ClockCalendar(clock_time_t new_time, calendar_date_t new_date, bool rtc_initializer);

    void setCustomTimeAndDate(int month, int day, int year, int hour, int minute, int second, bool is_pm);

    void readClockCalendar(calendar_date_t& readDate, clock_time_t& currentTime);    

    void advance();
};

#endif /* CLK_CAL_HPP_ */
