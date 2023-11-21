/**
 * @file main.hpp
 * @brief Main file of the embedded system
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */

/* 
 *  Embedded System Main File
 */

//#include <stdio.h>
//#include "pico/stdlib.h"

//#include <PicoLed.hpp>
//#include "PicoLed.hpp"
//#include "BH1750FVI.hpp"
//#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"
#include "Control.hpp"
#include "Logger.hpp"


#define LED_PIN 0
#define LED_LENGTH 5

int main()
{
    stdio_init_all();
    sleep_ms(1000);

    // Structure for working with the SDK rtc library
    datetime_t t = {
            .year  = 2023,
            .month = 11,
            .day   = 19,
            .dotw  = 0,
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

    // Initialize your LED strip, sensor, and other components
    // Replace the placeholder values with the actual initialization parameters
    auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LED_PIN, LED_LENGTH, PicoLed::FORMAT_GRB);
    BH1750FVI lightSensor(BH1750FVI::devAddr_L, BH1750FVI::contHighRes);
    lightSensor.setSDAPin(16);
    lightSensor.setSCLPin(17);
    lightSensor.begin();

    // 1. Set all LEDs to ambient 1!
    printf("1. Set all LEDs to ambient 1!\n");
    ledStrip.fill( PicoLed::RGB(255, 220, 185) );
    ledStrip.setBrightness(0);      // This initiates the led strip off
    ledStrip.show();
    sleep_ms(500);

    // Create an instance of the Control class
    PicoLed::PicoLedController ledStripController(ledStrip);
    Control controller(ledStripController, lightSensor);

    // Set the target light intensity
    controller.setTargetLightIntensity(15000);  // Set the target light intensity

    // Timestamp for the buffer
    char timestampBuffer[20];

    // Object logger for the Logger class
    Logger logger;

    std::vector<std::string> logs;  // Container to store logs

    // Auxiliar variables for a new log
    bool newLog;
    uint8_t newSec = 100; // initiates with an invalid second

    // Main loop
    while (1) {    

        // Retrieve and print the light intensity
        controller.adjustBrightness();
        printf("\n\rLight Intensity: %u lux    Brightness: %u     ", controller.getLightIntensity(), ledStrip.getBrightness());
        //printf("Brightness: %u \n", ledStrip.getBrightness());

        // get a new date and time for the timestamp
        rtc_get_datetime(&t);

        // Converting the base datetime_t members into the ISO8601 standard
        snprintf(timestampBuffer, sizeof(timestampBuffer), "%d-%02d-%02dT%02d:%02d:%02d",
             t.year, t.month, t.day, t.hour, t.min, t.sec);
        printf("%s\n", timestampBuffer);

        // Time based condition to create a new log
        newLog = t.sec == 0 || t.sec == 15 || t.sec == 30 || t.sec == 45;
        if (newLog == true && newSec != t.sec ) {
            // Adding logs to the container
            logs.push_back(std::string(timestampBuffer) + " : Light Intensity: " + std::to_string(controller.getLightIntensity()) + " lux : Brightness: " + std::to_string(ledStrip.getBrightness()));
            newSec = t.sec;
        }

        // Print the size of the logs vector
        printf("Logs vector size: %zu\n", logs.size());

        // Sleep between iterations
        sleep_ms(10);
    }

    return 0;
}
