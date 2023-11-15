/**
 * @file BH1750FVI.hpp
 * @brief Definition of the BHF1750FVI class for the sensor
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

#ifndef BH1750FVI_HPP_
#define BH1750FVI_HPP_

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0

class BH1750FVI {

public:

    typedef enum deviceAddr {
        devAddr_L = 0x23,        // ADDR pin connected to GND
        devAddr_H = 0x5C         // ADDR pin connected to VCC
     } deviceAddr_t;

    typedef enum deviceMode {
        contHighRes  = 0x10,     // continuos reading 0.5 lx resolution (120 ms)
        contHighRes2 = 0x11,     // continuos reading 1 lx resolution (120 ms)
        contLowRes   = 0x13,     // continuos reading 4 lx resolution (16 ms)
        oneHighRes   = 0x20,     // single read 0.5 lx resolution (120 ms)
        oneHighRes2  = 0x21,     // single read 1 lx resolution (120 ms)
        oneLowRes    = 0x23      // single read 4 lx resolution (16 ms)
    } deviceMode_t;

    typedef enum deviceState {
        powerDown = 0x00,        // No active state
        powerUp = 0x01,          // Waiting for measurement command
        reset = 0x07             // Reset Data register command. Device must be active (powerUp)
    } deviceState_t;

    BH1750FVI(deviceMode_t deviceMode);

    uint16_t GetLightIntensity(void);  

    void begin(void);

    void Sleep(void);

    void SetMode(deviceMode_t deviceMode);

    void Reset(void);    

    void setAddress(deviceAddr_t deviceAddr);

    void setSDAPin(uint8_t sdaPin);
    
    void setSCLPin(uint8_t sclPin);

    void i2c_write_blocking(uint8_t Data); 

private:
    
    uint8_t m_sdaPin;
    uint8_t m_sclPin;
    uint8_t SDA;                //!< SDA pin of the device
    uint8_t SCL;                //!< SCL pin of the device
    deviceAddr_t m_deviceAddr;  //!< I2C address of the device
    deviceMode_t m_deviceMode;  //!< Mode of the device
    bool m_addrPinUsed;         //!< Constructed with or without the address pin
};

#endif /* BH1750FVI_HPP_ */