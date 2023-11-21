#include <stdio.h>
#include "pico/stdlib.h"

#include <PicoLed.hpp>
#include "ClockCalendar.hpp"
#include "BH1750FVI.hpp"
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#define LED_PIN 0
#define LED_LENGTH 5

int main()
{
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

    BH1750FVI lightSensor(BH1750FVI::devAddr_L, BH1750FVI::contHighRes); 

    lightSensor.setSDAPin(16);
    lightSensor.setSCLPin(17);

    lightSensor.begin();

    // 0. Initialize LED strip
    printf("0. Initialize LED strip\n");
    auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LED_PIN, LED_LENGTH, PicoLed::FORMAT_GRB);
    ledStrip.setBrightness(50);
    printf("1. Clear the strip!\n");
    
    // 1. Set all LEDs to ambient 1!
    printf("1. Set all LEDs to ambient 1!\n");
    ledStrip.fill( PicoLed::RGB(255, 220, 185) );
    ledStrip.show();
    sleep_ms(500);

    while(1) {

        for (uint16_t bright_lvl = 0; bright_lvl <= 250; bright_lvl += 25) {
            ledStrip.setBrightness(bright_lvl);
            ledStrip.show();
            //printf("Brightness Level:\n", ledStrip.getBrightness());
            sleep_ms(250);  // Adjust the sleep duration as needed
        }
        
        rtc_get_datetime(&t);
        datetime_to_str(datetime_str, sizeof(datetime_buf), &t);
        printf("\r%s      \n", datetime_str);

        uint16_t lightIntensity = lightSensor.getLux();
        printf("Light Intensity: %u lux\n", lightIntensity);

        for (uint16_t bright_lvl = 250; bright_lvl > 0; bright_lvl -= 25) {
            ledStrip.setBrightness(bright_lvl);
            ledStrip.show();
            //printf("Brightness Level:\n", ledStrip.getBrightness());
            sleep_ms(250);  // Adjust the sleep duration as needed
        }

        lightIntensity = lightSensor.getLux();
        printf("Light Intensity: %u lux\n", lightIntensity);
    }
    return 0;
}