/**
 * @file BH1750FVI.hpp
 * @brief Implementation of the BHF1750FVI class for the sensor
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 14/11/2023
 * @institution UFSC
 */

/*
    File based on the library made by PeterEmbedded
    Source: https://github.com/PeterEmbedded/BH1750FVI
*/

/* 
 *  Digital Light sensor BH1750FVI (GY-302)
 */

#include "BH1750FVI.hpp"

BH1750FVI::BH1750FVI(deviceMode_t deviceMode) : m_deviceAddr(devAddr_L) {

}

void BH1750FVI::setSDAPin(uint8_t sdaPin) {
    m_sdaPin = sdaPin;
}

void BH1750FVI::setSCLPin(uint8_t sclPin) {
    m_sclPin = sclPin;
}

void BH1750FVI::begin(void)
{
    i2c_init(I2C_PORT, 100 * 1000);   // Set I2C clock frequency to 100 kHz
    printf("trying to Power up sensor...\n");
    uint8_t powerUpByte = static_cast<uint8_t>(powerUp);
    ::i2c_write_blocking(I2C_PORT, m_deviceAddr, &powerUpByte, 1, false); // Turn the driver On
    sleep_ms(10);  // Add a delay after power up
    printf("addressed and powered up...\n");
    if (m_addrPinUsed) {
        gpio_set_function(m_sdaPin, GPIO_FUNC_I2C);
        gpio_set_function(m_sclPin, GPIO_FUNC_I2C);
        gpio_pull_up(m_sdaPin);
        gpio_pull_up(m_sclPin);
        setAddress(m_deviceAddr); // Set the address
    }
    SetMode(m_deviceMode);        // Set the mode
    printf("sensor powered up...\n");
}
  
void BH1750FVI::Sleep(void)
{
    i2c_write_blocking(powerDown); // Turn it off
}

void BH1750FVI::Reset(void)
{
    i2c_write_blocking(powerUp);  // Turn it on before we can reset it
    i2c_write_blocking(reset);   // Reset
}

void BH1750FVI::setAddress(deviceAddr_t deviceAddr) {
    m_deviceAddr = deviceAddr;
}

void BH1750FVI::SetMode(deviceMode_t deviceMode)
{
    m_deviceMode = deviceMode;
    sleep_ms(10);
    i2c_write_blocking(m_deviceMode);
}

uint16_t BH1750FVI::GetLightIntensity(void)
{
    uint8_t sensorData_half[2];
    uint16_t sensorData;

    i2c_set_slave_mode(I2C_PORT, true, m_deviceAddr);
    i2c_read_blocking(I2C_PORT, m_deviceAddr, sensorData_half, 2, false);
    sensorData = (uint16_t)(sensorData_half[1] << 8 | sensorData_half[0]);

    return sensorData;
}

void BH1750FVI::i2c_write_blocking(uint8_t Data)
{
    uint8_t buffer[1] = {Data};
    ::i2c_write_blocking(I2C_PORT, m_deviceAddr, buffer, 1, false);
}