/**
 * @file rtcTest.cpp
 * @brief New time and date formats for the original SDK functions
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */


#include <stdio.h>
#include <cstring>
#include "PicoRTC.hpp"
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

int main() {
    stdio_init_all();
    sleep_ms(1000);
    
    char datetime_buf[256];
    char *datetime_str = &datetime_buf[0];

    // Start on Sunday 19th of November 2023 15:45:00
    datetime_t t = {
            .year  = 2023,
            .month = 11,
            .day   = 19,
            .dotw  = 0, // 0 is Sunday, so 5 is Friday
            .hour  = 15,
            .min   = 45,
            .sec   = 00
    };

    // Start the RTC
    rtc_init();
    rtc_set_datetime(&t);

    // clk_sys is >2000x faster than clk_rtc, so datetime is not updated immediately when rtc_get_datetime() is called.
    // tbe delay is up to 3 RTC clock cycles (which is 64us with the default clock settings)
    sleep_us(64);

    // Main loop
    while (1) {   
        rtc_get_datetime(&t);
        datetime_to_str(datetime_str, sizeof(datetime_buf), &t);

        // Manipulate the result string
        char manipulated_datetime[256];
        new_datetime_str(manipulated_datetime, sizeof(manipulated_datetime), datetime_str);
        printf("\r%s      \n\n", manipulated_datetime);

        printf("\rYear: %d, Month: %d, Day: %d, Hour: %d, Minute: %d, Second: %d      \n\n",
            t.year, t.month, t.day, t.hour, t.min, t.sec);

        sleep_ms(1000);
    }
    return 0;
}