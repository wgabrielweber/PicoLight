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

void SerialCommunication::Run() {
    while (true) {
        ReadFromSerialPort();

        // Send data to serial port (replace this with your test data)
        const char* testData = "Test data from Windows";
        WriteToSerialPort(testData, strlen(testData));

        Sleep(100); // Adjust the sleep duration as needed
    }
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

void SerialCommunication::ReadFromSerialPort() {
    DWORD bytesRead;
    char inByte;

    if (ReadFile(serialHandle, &inByte, 1, &bytesRead, NULL)) {
        if (bytesRead > 0) {
            // Handle the incoming byte
            std::cout << inByte;
        }
    } else {
        std::cerr << "Error reading from serial port\n";
    }
}

void SerialCommunication::WriteToSerialPort(const char* data, DWORD dataSize) {
    DWORD bytesWritten;

    if (WriteFile(serialHandle, data, dataSize, &bytesWritten, NULL)) {
        if (bytesWritten > 0) {
            std::cout << "Data sent to serial port\n";
        }
    } else {
        std::cerr << "Error writing to serial port\n";
    }
}
