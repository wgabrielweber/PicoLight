/**
 * @file Control.hpp
 * @brief Test file for the Control class of the PID Control Syistem
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */

/* 
 *  PID Controller
 */

#include "Control.hpp"
#include "PicoLed.hpp"  
#include "BH1750FVI.hpp"

#define LED_PIN 0
#define LED_LENGTH 5

int main() {
    stdio_init_all();
    sleep_ms(1000);

    // Initialize your LED strip, sensor, and other components
    // Replace the placeholder values with your actual initialization parameters
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

    // Set PID gains
    controller.setPIDGains(4, 0.05, 2);

    // Set smoothing factor (adjust as needed)get
    controller.setSmoothingFactor(1.0);

    // Set the target light intensity
    controller.setTargetLightIntensity(15000);  // Set the target light intensity

    controller.setMaxBrightnessChange(1);  // Set the desired maximum change (Brightness levels goes from 0 to 255)

    std::string userInput; // used for the user interface

    // Main loop
    while (1) {    
     
        // Retrieve and print the light intensity
        controller.adjustBrightness();
        printf("Light Intensity: %u lux    Brightness: %u \n", controller.getLightIntensity(), ledStrip.getBrightness());
        //printf("Brightness: %u \n", ledStrip.getBrightness());

        // Sleep or delay as needed between iterations
        sleep_ms(10);
    }
    return 0;
}
