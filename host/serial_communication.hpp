 /**
 * @file serial_communication.hpp
 * @brief Serial Communication header file
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 28/11/2023
 * @institution UFSC
 */

#ifndef SERIAL_COMMUNICATION_HPP
#define SERIAL_COMMUNICATION_HPP

#include <iostream>
#include <windows.h>
#include "logger.hpp"

//#define MAX_MESSAGE_LENGTH 14

class SerialCommunication {
public:
    SerialCommunication(const char* portName);
    ~SerialCommunication();

    bool Initialize();

    void WriteToSerialPort(const char* data, DWORD dataSize);
    void ReadFromSerialPort(Logger& logger);
    bool dataSentFlag;
    bool errorFlag;
    HANDLE serialHandle;

private:
    DCB dcbSerialParams;
    COMMTIMEOUTS timeouts;

    const char* portName;

    bool OpenSerialPort();
    bool SetSerialParameters();
    bool SetTimeouts();
};

#endif // SERIAL_COMMUNICATION_HPP
