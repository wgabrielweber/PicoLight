// WS2812b.hpp
#ifndef WS2812B_HPP
#define WS2812B_HPP

#include "pwm_control.hpp"

class LED {
public:
    LED(uint8_t pin);

    void setDutyCycle(uint16_t duty_cycle);

private:
    uint8_t gpioPin;
};

#endif // WS2812B_HPP
