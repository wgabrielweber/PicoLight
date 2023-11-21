/**
 * @file Control.hpp
 * @brief Implementation of the Control class for PID Control Syistem
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */

/* 
 *  PID Controller
 */

#include "Control.hpp"

Control::Control(PicoLed::PicoLedController& ledStrip, BH1750FVI& lightSensor)
    : ledStrip_(ledStrip), lightSensor_(lightSensor), targetIntensity_(0), integral_(0), previousError_(0) {
    // Constructor code, if needed
}

// In Control.cpp
void Control::setPIDGains(double Kp, double Ki, double Kd) {
    Kp_ = Kp;
    Ki_ = Ki;
    Kd_ = Kd;
}

void Control::setSmoothingFactor(double smoothingFactor) {
    smoothingFactor_ = smoothingFactor;
}

void Control::setTargetLightIntensity(uint16_t targetIntensity) {
    targetIntensity_ = targetIntensity;
}

void Control::setMaxBrightnessChange(uint8_t maxChange) {
    maxBrightnessChange_ = maxChange;
}

void Control::adjustBrightness() {
    // Retrieve light intensity
    uint16_t lightIntensity = lightSensor_.getLux();
    //sleep_ms(150); // the sensor needs time to make a measure
    LightIntensity_ = lightIntensity; // Store the last read value

    // Map light intensity to initial brightness (adjust this mapping as needed)
    //uint8_t initialBrightness = static_cast<uint8_t>((lightIntensity - 0) * (255 - 0) / (50000 - 0) + 0);
    //uint8_t initialBrightness = 0; // always start with the led strip off

    // Perform PID-controlled brightness adjustment
    int16_t error = targetIntensity_ - lightIntensity;
    integral_ += error;
    int16_t derivative = error - previousError_;
    float output = Kp_ * error + Ki_ * integral_ + Kd_ * derivative;
    
    // Calculate the new brightness from the PID output
    uint8_t pidBrightness = static_cast<uint8_t>(output);

    // Get the actual brightness of the LED strip
    uint8_t actualBrightness = ledStrip_.getBrightness();

    // Apply smoothing to the actual brightness
    uint8_t smoothedBrightness = static_cast<uint8_t>(previousControlOutput_ + smoothingFactor_ * (pidBrightness - previousControlOutput_));
    
    // Limit the maximum change in brightness
    int brightnessChange = std::min<int>(std::max<int>(smoothedBrightness - actualBrightness, -maxBrightnessChange_), maxBrightnessChange_);

    smoothedBrightness = actualBrightness + brightnessChange;
    previousControlOutput_ = smoothedBrightness;

    // Set LED strip brightness
    ledStrip_.setBrightness(smoothedBrightness);
    ledStrip_.show();

    previousError_ = error;
}