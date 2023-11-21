/**
 * @file Control.hpp
 * @brief Control class for the second Control Syistem
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */

/* 
 *  PID Controller
 */

#ifndef CONTROL_HPP_
#define CONTROL_HPP_

#include <cmath>
#include <cstdlib>
#include <stdio.h>

#include <PicoLed.hpp>
#include "pico/stdlib.h"
#include "BH1750FVI.hpp"
#include "pico/stdlib.h"

class Control {
public:
    Control(PicoLed::PicoLedController& ledStrip, BH1750FVI& lightSensor);

    // Function to set the target light intensity
    void setTargetLightIntensity(uint16_t targetIntensity);

    // Function to adjust brightness using PID control
    void adjustBrightness();

    // Getter for the last light intensity
    uint16_t getLightIntensity() const {
        return LightIntensity_;
    }    

private:
    PicoLed::PicoLedController& ledStrip_;
    BH1750FVI& lightSensor_;

    uint16_t LightIntensity_;
    uint16_t targetIntensity_;
};

#endif /* CONTROL_HPP_ */