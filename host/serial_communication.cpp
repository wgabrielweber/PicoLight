#include "serial_communication.hpp"

SerialCommunication::SerialCommunication(const char* port)
    : portName(port), serialHandle(INVALID_HANDLE_VALUE) {
}

SerialCommunication::~SerialCommunication() {
    if (serialHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(serialHandle);
    }
}

bool SerialCommunication::Initialize() {
    if (!OpenSerialPort()) {
        std::cerr << "Error opening serial port\n";
        return false;
    }

    if (!SetSerialParameters()) {
        std::cerr << "Error setting serial port parameters\n";
        CloseHandle(serialHandle);
        return false;
    }

    if (!SetTimeouts()) {
        std::cerr << "Error setting timeouts\n";
        CloseHandle(serialHandle);
        return false;
    }
   
    return true;
}

bool SerialCommunication::OpenSerialPort() {
    serialHandle = CreateFileA(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    return (serialHandle != INVALID_HANDLE_VALUE);
}

bool SerialCommunication::SetSerialParameters() {
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(serialHandle, &dcbSerialParams)) {
        std::cerr << "Error getting serial port state\n";
        return false;
    }

    dcbSerialParams.BaudRate = CBR_115200;  // Update baud rate
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    // Set flow control
    dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;
    dcbSerialParams.fRtsControl = RTS_CONTROL_ENABLE;

    return SetCommState(serialHandle, &dcbSerialParams);
}

bool SerialCommunication::SetTimeouts() {
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    return SetCommTimeouts(serialHandle, &timeouts);
}

void SerialCommunication::WriteToSerialPort(const char* data, DWORD dataSize) {
    // Append a newline character at the end of the message
    std::string messageWithNewline(data, dataSize);
    messageWithNewline += '\n';

    DWORD bytesWritten;
    
    if (WriteFile(serialHandle, messageWithNewline.c_str(), messageWithNewline.size(), &bytesWritten, NULL)) {
        if (bytesWritten > 0) {
//            std::cout << "Data sent to serial port\n";
//            std::cout << messageWithNewline + "\n";
            dataSentFlag = true;  // Set data sent flag
        }
    } else {
        std::cerr << "Error writing to serial port\n";
        errorFlag = true;  // Set error flag
    }

    Sleep(10);
}

void SerialCommunication::ReadFromSerialPort() {

    const int bufferSize = 256; // Adjust the buffer size as needed
    char buffer[bufferSize];
    DWORD bytesRead;

    if (ReadFile(serialHandle, buffer, bufferSize, &bytesRead, NULL)) {
        if (bytesRead > 0) {
            std::string receivedMessage(buffer, bytesRead);
            std::cout << receivedMessage << std::endl;
        }
    } else {
        std::cerr << "Error reading from serial port\n";
        errorFlag = true;  // Set error flag
    }

    Sleep(10);
}