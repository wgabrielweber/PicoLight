// WS2812b.cpp
#include "WS2812b.hpp"

LED::LED(uint8_t pin) : gpioPin(pin) {
    // Additional initialization if needed
}

void LED::setDutyCycle(uint16_t duty_cycle) {
    set_pwm_duty_cycle(duty_cycle);
}