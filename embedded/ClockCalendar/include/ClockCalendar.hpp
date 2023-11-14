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

/**
 * @class ClockCalendar
 * @brief Class for managing both time and date.
 */
class ClockCalendar : public Clock, public Calendar {
public:
    /**
     * @brief Default constructor for the ClockCalendar class.
     * @param rtc_initializer Flag to initialize from RTC.
     */
    ClockCalendar(bool rtc_initializer);

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
     */
    ClockCalendar(int month, int day, int year, int hour, int minute, int second, bool is_pm, bool rtc_initializer);

    /**
     * @brief Constructor for the ClockCalendar class with clock_time_t and calendar_date_t structs.
     * 
     * @param new_time New time to set.
     * @param new_date New date to set.
     * @param rtc_initializer Flag to initialize from RTC.
     */
    ClockCalendar(clock_time_t new_time, calendar_date_t new_date, bool rtc_initializer);

    /**
     * @brief Set personalized time and date.
     * 
     * @param hour Hour.
     * @param minute Minutes.
     * @param second Seconds.
     * @param is_pm am:pm indicator.
     * @param month Month.
     * @param day Day.
     * @param year Year.
     */
    void setCustomTimeAndDate(int month, int day, int year, int hour, int minute, int second, bool is_pm);    

    /**
     * @brief Advances the clock by one second.
     */
    void advance();
};

#endif /* CLK_CAL_HPP_ */
