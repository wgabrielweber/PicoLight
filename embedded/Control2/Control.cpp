/**
 * @file Control.hpp
 * @brief Implementation for the second Control Syistem
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */

/* 
 *  Control 2
 */

#include "Control.hpp"

Control::Control(PicoLed::PicoLedController& ledStrip, BH1750FVI& lightSensor)
    : ledStrip_(ledStrip), lightSensor_(lightSensor), targetIntensity_(0) {
}

void Control::setTargetLightIntensity(uint16_t targetIntensity) {
    targetIntensity_ = targetIntensity;
}

void Control::adjustBrightness() {

    // auxiliary variables
    uint16_t targetUpper = targetIntensity_ + 500;
    uint16_t targetLower = targetIntensity_ - 500;
    uint8_t newBrightness;

    // Retrieve light intensity
    uint16_t lightIntensity = lightSensor_.getLux();
    LightIntensity_ = lightIntensity; // Store the last read value

    // Get the actual brightness of the LED strip
    uint8_t actualBrightness = ledStrip_.getBrightness();

    if (LightIntensity_ > targetUpper) {
        if (actualBrightness >= 0) {
            if (abs(LightIntensity_ - targetUpper) > 5000) {
            // Set LED strip brightness
            newBrightness = std::min(255, std::max(0, actualBrightness - 5));
            ledStrip_.setBrightness(newBrightness);
            ledStrip_.show();
        } else {
            newBrightness = std::min(255, std::max(0, actualBrightness - 1));
            ledStrip_.setBrightness(newBrightness);
            ledStrip_.show();    
        }
        }
    }
    if (LightIntensity_ < targetLower) {
        if (actualBrightness <= 255) {
            if (abs(LightIntensity_ - targetLower) > 5000) {
                // Set LED strip brightness
                newBrightness = std::min(255, std::max(0, actualBrightness + 5));
                ledStrip_.setBrightness(newBrightness);
                ledStrip_.show();
            } else {
                newBrightness = std::min(255, std::max(0, actualBrightness + 1));
                ledStrip_.setBrightness(newBrightness);
                ledStrip_.show();
            }
        }
    }
}
