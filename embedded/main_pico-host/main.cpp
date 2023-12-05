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
#include <tusb.h>
#include <vector>

#include "hardware/rtc.h"
#include "pico/util/datetime.h"
#include "Control.hpp"
#include "Logger.hpp"
#include "SerialCommunication.hpp"

#define LED_PIN 13
#define LED_LENGTH 10

int main()
{
    stdio_init_all();
    sleep_ms(1000);
    
    bool rtc_set = false;

/*--------------SERIAL COMMUNICATION AND RTC INITIALIZATION--------------*/

    SerialCommunication serialCommunication;
    // Start listening for messages
    serialCommunication.startListening();

    // Get the received message
    std::string receivedMessage = serialCommunication.getReceivedMessage();

    // Split the string
    std::string str_year = receivedMessage.substr(0,4);
    std::string str_month = receivedMessage.substr(4,2);
    std::string str_day = receivedMessage.substr(6,2);
    std::string str_hour = receivedMessage.substr(8,2);
    std::string str_min = receivedMessage.substr(10,2);
    std::string str_sec = receivedMessage.substr(12,2);

    // Convert the string into integers
    int16_t year = std::stoi(str_year);
    int8_t month = std::stoi(str_month);
    int8_t day = std::stoi(str_day);
    int8_t hour = std::stoi(str_hour);
    int8_t minute = std::stoi(str_min);
    int8_t second = std::stoi(str_sec);

    // Structure for working with the SDK rtc library
    datetime_t t = {
        .year  = year,
        .month = month,
        .day   = day,
        .dotw  = 0,
        .hour  = hour,
        .min   = minute,
        .sec   = second
    };

    // Start the RTC
    rtc_init();
    rtc_set_datetime(&t);

    // clk_sys is >2000x faster than clk_rtc, so datetime is not updated immediately when rtc_get_datetime() is called.
    // tbe delay is up to 3 RTC clock cycles (which is 64us with the default clock settings)
    sleep_us(64);

    // Reset the messageReceived flag
    serialCommunication.resetMessageReceived();

/*-----------------------------------------------------------------------*/
/*--------------------------ACTUATOR AND CONTROL-------------------------*/

    // Replace the placeholder values with the actual initialization parameters
    auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LED_PIN, LED_LENGTH, PicoLed::FORMAT_GRB);
    BH1750FVI lightSensor(BH1750FVI::devAddr_L, BH1750FVI::oneHighRes);
    lightSensor.setSDAPin(16);
    lightSensor.setSCLPin(17);
    lightSensor.begin();

    // 1. Set all LEDs to ambient 1!
    ledStrip.fill( PicoLed::RGB(255, 220, 185) );
    ledStrip.setBrightness(0);      // This initiates the led strip off
    ledStrip.show();
    sleep_ms(500);

    // Create an instance of the Control class
    PicoLed::PicoLedController ledStripController(ledStrip);
    Control controller(ledStripController, lightSensor);

    // Set the target light intensity
    controller.setTargetLightIntensity(7250);  // Set the target light intensity

/*-----------------------------------------------------------------------*/
/*-------------------------------LOGGER----------------------------------*/

    // buffer for the firstTime (used to get the active time)
    char firstTime[20];
    // Converting the base datetime_t members into the ISO8601 standard
    snprintf(firstTime, sizeof(firstTime), "%d-%02d-%02dT%02d:%02d:%02d",
        t.year, t.month, t.day, t.hour, t.min, t.sec);
    printf("\nInitialization Timestamp: %s\n", firstTime);

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

/*-----------------------------------------------------------------------*/

    // Main loop
    while (1) {    

/*--------------------------------CONTROL--------------------------------*/

        // adjustBrightness is the function from the control class responsible
        // to get the current light intensity and adjust the LED brightness
        controller.adjustBrightness();

/*---------------------------------TIME----------------------------------*/

        // get a new date and time for the timestamp
        rtc_get_datetime(&t);

        // Converting the base datetime_t members into the ISO8601 standard
        snprintf(timestampBuffer, sizeof(timestampBuffer), "%d-%02d-%02dT%02d:%02d:%02d",
             t.year, t.month, t.day, t.hour, t.min, t.sec);
//        printf("%s\n", timestampBuffer);

        // parsing timestampBuffer to Unix time to calculate the active time
        std::tm tm_timestampBuffer = {};
        std::istringstream timestampBufferStream(timestampBuffer);
        timestampBufferStream >> std::get_time(&tm_timestampBuffer, "%Y-%m-%dT%H:%M:%S");
        std::time_t unixtime_timestampBuffer = std::mktime(&tm_timestampBuffer);

        // Calculate the active time in seconds
        int diffSeconds = unixtime_timestampBuffer - unixtime_firstTime;

/*-------------------------------LOGGER----------------------------------*/

        // Time based condition to create a new log
        newLog = t.sec == 0 || t.sec == 15 || t.sec == 30 || t.sec == 45;
        if (newLog == true && newSec != t.sec ) {
            // Adding logs to the container
            logs.push_back(std::string(timestampBuffer) + " | " + std::to_string(controller.getLightIntensity())
                 + " | " + std::to_string(ledStrip.getBrightness()) + " | " + std::to_string(diffSeconds) + "\n");
            newSec = t.sec;

        // Printing Results
        printf("%s | %u | %u | %d \n", timestampBuffer, controller.getLightIntensity(), ledStrip.getBrightness(), diffSeconds);

            // Print all logs
//            for (const auto& log : logs) {
//                printf("%s\n", log.c_str());
//            }
        }
        // Sleep between iterations
        sleep_ms(10);
    }

    return 0;
}