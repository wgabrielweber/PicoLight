/**
 * @file pwm_control_.hpp
 * @brief Test file for the pwm controller.
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 16/11/2023
 * @institution UFSC
 */
/**
 *
 * This file was based on the pwm_led_fade_c from the Raspberry Pi Pico PWM examples
 *
**/

#include "pwm_control.hpp"

int main() {
    configure_pwm();

    // Everything after this point happens in the PWM interrupt handler, so we
    // can twiddle our thumbs
    while (1){
        for (uint16_t duty = 0; duty <= 255; ++duty) {
            set_pwm_duty_cycle(duty);
            sleep_ms(10);  // Adjust the sleep duration as needed
        }

        for (uint16_t duty = 255; duty > 0; --duty) {
            set_pwm_duty_cycle(duty);
            sleep_ms(10);  // Adjust the sleep duration as needed
        }
    }
    return 0;
}
