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

#include <sstream>
#include <iomanip>

#include "hardware/rtc.h"
#include "pico/util/datetime.h"
#include "Control.hpp"
#include "Logger.hpp"

#define LED_PIN 13
#define LED_LENGTH 10

int main()
{
    stdio_init_all();
    sleep_ms(1000);

/*------------------------------TIMESTAMP--------------------------------*/

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

/*-------------------------ACTUATOR AND CONTROL---------------------------*/

    // Replace the placeholder values with the actual initialization parameters
    auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LED_PIN, LED_LENGTH, PicoLed::FORMAT_GRB);
    BH1750FVI lightSensor(BH1750FVI::devAddr_L, BH1750FVI::oneHighRes);
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
    controller.setTargetLightIntensity(7500);  // Set the target light intensity

/*-------------------------------LOGGER----------------------------------*/

    // buffer for the firstTime (used to get the active time)
    char firstTime[20];
    // Converting the base datetime_t members into the ISO8601 standard
    snprintf(firstTime, sizeof(firstTime), "%d-%02d-%02dT%02d:%02d:%02d",
        t.year, t.month, t.day, t.hour, t.min, t.sec);
    printf("%s\n", firstTime);

    // parsing firstTime to Unix time to further calculate the active time
    std::tm tm_firstTime = {};
    std::istringstream firstTimeStream(firstTime);
    firstTimeStream >> std::get_time(&tm_firstTime, "%Y-%m-%dT%H:%M:%S");
    std::time_t unixtime_firstTime = std::mktime(&tm_firstTime);

    // buffer for the timestamp
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

        // get a new date and time for the timestamp
        rtc_get_datetime(&t);

        // Converting the base datetime_t members into the ISO8601 standard
        snprintf(timestampBuffer, sizeof(timestampBuffer), "%d-%02d-%02dT%02d:%02d:%02d",
             t.year, t.month, t.day, t.hour, t.min, t.sec);
        printf("%s\n", timestampBuffer);

        // parsing timestampBuffer to Unix time to calculate the active time
        std::tm tm_timestampBuffer = {};
        std::istringstream timestampBufferStream(timestampBuffer);
        timestampBufferStream >> std::get_time(&tm_timestampBuffer, "%Y-%m-%dT%H:%M:%S");
        std::time_t unixtime_timestampBuffer = std::mktime(&tm_timestampBuffer);

        // Calculate the active time in seconds
        int diffSeconds = unixtime_timestampBuffer - unixtime_firstTime;

        // Print the result
        printf("Time difference: %d seconds\n", diffSeconds);

        // Time based condition to create a new log
        newLog = t.sec == 0 || t.sec == 15 || t.sec == 30 || t.sec == 45;
        if (newLog == true && newSec != t.sec ) {
            // Adding logs to the container
            logs.push_back(std::string(timestampBuffer) + " : Light Intensity: " + std::to_string(controller.getLightIntensity())
                 + " lux : Brightness: " + std::to_string(ledStrip.getBrightness()) + " : Active Time: " + std::to_string(diffSeconds) + " seconds");
            newSec = t.sec;

            // Print the size of the logs vector
            printf("Logs vector size: %zu\n", logs.size());

            // Print all logs
            for (const auto& log : logs) {
                printf("%s\n", log.c_str());
        }

        }

        // Sleep between iterations
        sleep_ms(10);
    }

    return 0;
}
