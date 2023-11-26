#ifndef SERIAL_COMMUNICATION_HPP
#define SERIAL_COMMUNICATION_HPP

#include <iostream>
#include <windows.h>

#define MAX_MESSAGE_LENGTH 20

class SerialCommunication {
public:
    SerialCommunication(const char* portName);
    ~SerialCommunication();

    bool Initialize();
    void Run();

    void WriteToSerialPort(const char* data, DWORD dataSize);
    void ReadFromSerialPort();

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
