/**
 * @file testSensor.cpp
 * @brief Test program for the BHF1750FVI sensor
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 14/11/2023
 * @institution UFSC
 */

#include "BH1750FVI.hpp"

const unsigned int LED_PIN = PICO_DEFAULT_LED_PIN;

void init_led() {
    gpio_init(LED_PIN);
    gpio_set_function(LED_PIN, GPIO_FUNC_SIO);
    gpio_put(LED_PIN, 1);
}

int main() {
    stdio_init_all();
    init_led();

    BH1750FVI lightSensor(BH1750FVI::contHighRes);  // Using high-resolution mode as default

    lightSensor.setAddress(BH1750FVI::devAddr_L);
    lightSensor.setSDAPin(16);
    lightSensor.setSCLPin(17);

    while (1) {
        lightSensor.begin();

        uint16_t lightIntensity = lightSensor.GetLightIntensity();

        printf("Light Intensity: %u lux\n", lightIntensity);

        sleep_ms(1000);
    }

    return 0;
}