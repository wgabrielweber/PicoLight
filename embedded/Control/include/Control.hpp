/**
 * @file Control.hpp
 * @brief Control class for PID Control Syistem
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */

/* 
 *  PID Controller
 */

#ifndef CONTROL_HPP_
#define CONTROL_HPP_

#include <cmath>  // Include cmath for std::abs function

#include <stdio.h>
#include "pico/stdlib.h"

#include <PicoLed.hpp>
#include "BH1750FVI.hpp"
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"


class Control {
public:
    Control(PicoLed::PicoLedController& ledStrip, BH1750FVI& lightSensor);

    // Function to set the target light intensity
    void setTargetLightIntensity(uint16_t targetIntensity);

    // Function to adjust brightness using PID control
    void adjustBrightness();

    // Set PID gains
    void setPIDGains(double Kp, double Ki, double Kd);

    // Set smoothing factor
    void setSmoothingFactor(double smoothingFactor);

    // Function to set the maximum change in brightness
    void setMaxBrightnessChange(uint8_t maxChange);

    // Getter for the last light intensity
    uint16_t getLightIntensity() const {
        return LightIntensity_;
    }    

private:
    PicoLed::PicoLedController& ledStrip_;
    BH1750FVI& lightSensor_;

    // Smoothing factor for the control signal
    double smoothingFactor_;
    // Previous control output for smoothing
    double previousControlOutput_;

    double Kp_; // Adjust proportional gain
    double Ki_; // Adjust integral gain
    double Kd_; // Adjust derivative gain

    // Maximum change in brightness
    uint8_t maxBrightnessChange_;

    uint16_t targetIntensity_;
    int32_t integral_;
    int16_t previousError_;
    uint16_t LightIntensity_;
};

#endif /* CONTROL_HPP_ */