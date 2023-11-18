#include "WS2812b.hpp"

int main() {
    // Your initialization code here

    configure_pwm(); // Call once to configure PWM

    LED myLed(GPIO_PIN);

    while (true) {
        // Your main loop code here

        for (uint16_t duty = 0; duty <= 255; ++duty) {
            myLed.setDutyCycle(duty);
            sleep_ms(25);  // Adjust the sleep duration as needed
        }

        for (uint16_t duty = 255; duty > 0; --duty) {
            myLed.setDutyCycle(duty);
            sleep_ms(25);  // Adjust the sleep duration as needed
        }
    }

    return 0;
}