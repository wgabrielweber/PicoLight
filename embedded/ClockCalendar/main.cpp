#include <stdio.h>
#include "pico/stdlib.h"
#include "ClockCalendar.hpp"

int main() {
    stdio_init_all();
    printf("ClockCalendar Example\n");

    // Create a ClockCalendar object with initial values
    ClockCalendar clockCalendar(false);

    while (true) {
        // Advance the clock by one second
        clockCalendar.advance();

        // Get the current time and date
        clock_time_t currentTime;
        calendar_date_t currentDate;
        clockCalendar.readClock(currentTime);
        clockCalendar.readCalendar(currentDate);

        // Print the time and date
        printf("\r%02d/%02d/%04d %02d:%02d:%02d %s      ",
               currentDate.month, currentDate.day, currentDate.year,
               currentTime.hour, currentTime.min, currentTime.sec,
               currentTime.is_pm ? "PM" : "AM");

        sleep_ms(1000); // Delay for one second
    }

    return 0;
}
