/**
 * @file testSensor.cpp
 * @brief Test program for the BHF1750FVI sensor
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 14/11/2023
 * @institution UFSC
 */

#include "BH1750FVI.hpp"

int main() {
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    BH1750FVI lightSensor(BH1750FVI::contHighRes);  // Using high-resolution mode as default

    lightSensor.setAddress(BH1750FVI::devAddr_L);
    lightSensor.setSDAPin(16);
    lightSensor.setSCLPin(17);

    while (1) {
        gpio_put(25, 1);
        printf("LED ON!\n");
        sleep_ms(10000);        
    
        gpio_put(25, 0); // Set pin 25 to low
        printf("LED OFF!\n");
        sleep_ms(1000);

        lightSensor.begin();
        printf("Sensor initialized!\n");
        uint16_t lightIntensity = lightSensor.GetLightIntensity();
        printf("Light Intensity: %u lux\n", lightIntensity);
        sleep_ms(500); // 0.5s delay
    }

    return 0;
}