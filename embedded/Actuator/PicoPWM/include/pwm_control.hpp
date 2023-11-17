/**
 * @file pwm_control_.hpp
 * @brief Header file for the PWM control
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 16/11/2023
 * @institution UFSC
 */
/**
 *
 * This file was based on the pwm_led_fade_c from the Raspberry Pi Pico PWM examples
 *
**/

#ifndef PWM_CONTROL_HPP
#define PWM_CONTROL_HPP

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"

#define GPIO_PIN 14

#ifdef __cplusplus
extern "C" {
#endif

void on_pwm_wrap(void);
void configure_pwm(void);
void set_pwm_duty_cycle(uint16_t duty_cycle);

#ifdef __cplusplus
}
#endif

#endif // PWM_CONTROL_HPP