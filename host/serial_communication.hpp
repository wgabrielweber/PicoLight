#ifndef SERIAL_COMMUNICATION_HPP
#define SERIAL_COMMUNICATION_HPP

#include <iostream>
#include <windows.h>

//#define MAX_MESSAGE_LENGTH 14

class SerialCommunication {
public:
    SerialCommunication(const char* portName);
    ~SerialCommunication();

    bool Initialize();

    void WriteToSerialPort(const char* data, DWORD dataSize);
    void ReadFromSerialPort();
    bool dataSentFlag;
    bool errorFlag;

private:
    HANDLE serialHandle;
    DCB dcbSerialParams;
    COMMTIMEOUTS timeouts;

    const char* portName;

    bool OpenSerialPort();
    bool SetSerialParameters();
    bool SetTimeouts();
};

#endif // SERIAL_COMMUNICATION_HPP
