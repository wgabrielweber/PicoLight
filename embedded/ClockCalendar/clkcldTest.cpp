/**
 * @file clkcldTest.cpp
 * @brief Testing file for the ClockCalendar class.
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 14/11/2023
 * @institution UFSC
 */

#include "ClockCalendar.hpp"

int main() {
    // Initialize standard I/O
    stdio_init_all();
    // Print a message indicating the start of the ClockCalendar example
    printf("ClockCalendar Example\n");

    // Create a ClockCalendar object with initial values
    ClockCalendar clockCalendar(false);

    // Set a custom time and date (currently commented out)
    clockCalendar.setCustomTimeAndDate(10, 20, 2023, 10, 0, 0, false);

    while (true) {
        // Advance the clock by one second
        clockCalendar.advance();

        // Get the current time and date
        clock_time_t currentTime;
        calendar_date_t currentDate;
        //clockCalendar.readClock(currentTime);
        //clockCalendar.readCalendar(currentDate);
        clockCalendar.readClockCalendar(currentDate, currentTime);

        // Print the time and date
        printf("\r%02d/%02d/%04d %02d:%02d:%02d %s      ",
               currentDate.month, currentDate.day, currentDate.year,
               currentTime.hour, currentTime.min, currentTime.sec,
               currentTime.is_pm ? "PM \n" : "AM \n");

        // Delay for one second
        sleep_ms(1000);
    }

    // The program should never reach this point
    return 0;
}
