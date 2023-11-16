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

    BH1750FVI lightSensor(BH1750FVI::devAddr_L, BH1750FVI::contHighRes); 

    //lightSensor.setAddress(BH1750FVI::devAddr_L);   // Use devAddr_L if ADDR pin is connected to GND and devAddr_L if it is connected to VCC
    lightSensor.setSDAPin(16);
    lightSensor.setSCLPin(17);
    //lightSensor.setMode(BH1750FVI::contHighRes);    // Using high-resolution mode as default

    sleep_ms(5000);

    lightSensor.begin();
    printf("Sensor initialized!\n");
    sleep_ms(10);


    while (1) {
        gpio_put(25, 1);
        printf("LED ON!\n");
        sleep_ms(250);

        gpio_put(25, 0);
        printf("LED OFF!\n");
        sleep_ms(250);

        uint16_t lightIntensity = lightSensor.getLux();
        printf("Light Intensity: %u lux\n", lightIntensity);
        sleep_ms(500); 
    }
    return 0;
}