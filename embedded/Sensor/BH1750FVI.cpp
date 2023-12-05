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

BH1750FVI::BH1750FVI(eDeviceMode_t deviceMode)
{
    m_addrPinUsed = false;
    m_deviceAddr = devAddr_L;
}

BH1750FVI::BH1750FVI(eDeviceAddr_t deviceAddr, eDeviceMode_t deviceMode) :
  m_deviceAddr(deviceAddr),
  m_deviceMode(deviceMode)
{
  m_addrPinUsed = true;
}

void BH1750FVI::setSDAPin(uint8_t sdaPin) {
    m_sdaPin = sdaPin;
}

void BH1750FVI::setSCLPin(uint8_t sclPin) {
    m_sclPin = sclPin;
}

void BH1750FVI::setAddress(eDeviceAddr_t deviceAddr) {
    m_deviceAddr = deviceAddr;
}

void BH1750FVI::setMode(eDeviceMode_t deviceMode)
{
    m_deviceMode = deviceMode;
    sleep_ms(10);
    i2c_write_blocking(m_deviceMode);
}

void BH1750FVI::begin(void)
{
    printf("SDA Pin: %d, SCL Pin: %d, Address: %x, Mode: %x\n", m_sdaPin, m_sclPin, m_deviceAddr, m_deviceMode);

    // Set I2C pins
    gpio_set_function(getSDAPin(), GPIO_FUNC_I2C);
    gpio_set_function(getSCLPin(), GPIO_FUNC_I2C);
    gpio_pull_up(getSDAPin());
    gpio_pull_up(getSCLPin());
    setAddress(m_deviceAddr); // Set the address

    if (!i2c_init(I2C_PORT, 100 * 1000)) {          // Set I2C clock frequency to 100 kHz
        printf("I2C initialization failed.\n");     
        return;
    }
    sleep_ms(10);        // Add a delay before power up

    uint8_t powerOnByte = static_cast<uint8_t>(powerOn);
    uint8_t result = ::i2c_write_blocking(I2C_PORT, m_deviceAddr, &powerOnByte, 1, false);
    if (result == 1) {
        printf("Turned the driver on successfully.\n");
    } else {
        printf("Failed to turn on the driver. Error code: %u\n", result);
        return;
    }

    sleep_ms(10);  // Add a delay after power up

    setMode(m_deviceMode);        // Set the mode
    printf("sensor powered up...\n");
}
  
void BH1750FVI::Sleep(void)
{
    i2c_write_blocking(powerDown); // Turn it off
}

void BH1750FVI::Reset(void)
{
    i2c_write_blocking(powerOn);  // Turn it on before we can reset it
    i2c_write_blocking(reset);   // Reset
}

uint16_t BH1750FVI::getLux()
{
    // continuous modes
    if ((m_deviceMode & 0x10) && (m_deviceMode != m_deviceMode)) {
        setMode(m_deviceMode);
    }
    // one shot modes
    if (m_deviceMode & 0x20) {
        setMode(m_deviceMode);
    }
    
    // earlier measurements return previous reading
    sleep_ms((m_deviceMode == 0x13 || m_deviceMode == 0x23) ? 24 : 180);

    uint8_t sensorData_half[2];
    uint16_t sensorData;

    i2c_read_blocking(I2C_PORT, m_deviceAddr, sensorData_half, 2, false);
    sensorData = (uint16_t)(sensorData_half[1] << 8 | sensorData_half[0]);

    float factor = (m_deviceMode == 0x11 || m_deviceMode == 0x21) ? 2.0 : 1.0;
    return static_cast<uint16_t>(sensorData / (1.2 * factor));
}


void BH1750FVI::i2c_write_blocking(uint8_t Data)
{
    uint8_t buffer[1] = {Data};
    ::i2c_write_blocking(I2C_PORT, m_deviceAddr, buffer, 1, false);
}