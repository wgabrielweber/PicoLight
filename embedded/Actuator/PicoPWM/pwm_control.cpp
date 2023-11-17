/**
 * @file pwm_control_.cpp
 * @brief Implementation of the pwm control.
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

static int fade = 0;
static bool going_up = true;
static uint16_t duty_cycle = 0;

extern "C" {
    void on_pwm_wrap() {
        pwm_clear_irq(pwm_gpio_to_slice_num(GPIO_PIN));
        pwm_set_gpio_level(GPIO_PIN, duty_cycle * duty_cycle);
    }

    void configure_pwm() {
        // Tell the LED pin that the PWM is in charge of its value.
        gpio_set_function(GPIO_PIN, GPIO_FUNC_PWM);
        // Figure out which slice we just connected to the LED pin
        uint8_t slice_num = pwm_gpio_to_slice_num(GPIO_PIN);

        // Mask our slice's IRQ output into the PWM block's single interrupt line,
        // and register our interrupt handler
        pwm_clear_irq(slice_num);
        pwm_set_irq_enabled(slice_num, true);
        irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
        irq_set_enabled(PWM_IRQ_WRAP, true);

        // Get some sensible defaults for the slice configuration. By default, the
        // counter is allowed to wrap over its maximum range (0 to 2**16-1)
        pwm_config config = pwm_get_default_config();
        // Set divider, reduces counter clock to sysclock/this value
        pwm_config_set_clkdiv(&config, 4.f); // 125 kHz
        // Load the configuration into our PWM slice, and set it running.
        pwm_init(slice_num, &config, true);
    }
    
    void set_pwm_duty_cycle(uint16_t new_duty_cycle) {
        duty_cycle = new_duty_cycle;
}
}
