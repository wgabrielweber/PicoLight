#include <iostream>
#include <windows.h>
#include <string>

class SerialPort {
public:
    SerialPort(const wchar_t* portName) : portHandle(INVALID_HANDLE_VALUE) {
        // Open the serial port
        portHandle = CreateFileW(
            portName,
            GENERIC_READ,
            0,
            0,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            0
        );

        if (portHandle == INVALID_HANDLE_VALUE) {
            DWORD error = GetLastError();
            std::cerr << "Error opening serial port. Error code: " << error << std::endl;
        }
    }

    ~SerialPort() {
        // Close the serial port
        if (portHandle != INVALID_HANDLE_VALUE) {
            CloseHandle(portHandle);
        }
    }

    bool isOpen() const {
        return (portHandle != INVALID_HANDLE_VALUE);
    }

    bool setParams() {
        if (!isOpen()) {
            std::cerr << "Serial port is not open." << std::endl;
            return false;
        }

        // Set serial port parameters
        DCB serialParams = { 0 };
        serialParams.DCBlength = sizeof(serialParams);

        if (!GetCommState(portHandle, &serialParams)) {
            DWORD error = GetLastError();
            std::cerr << "Error getting serial port state. Error code: " << error << std::endl;
            return false;
        }

        serialParams.BaudRate = CBR_115200;  // Set the baud rate to 115200 bps
        serialParams.ByteSize = 8;           // 8 data bits
        serialParams.StopBits = ONESTOPBIT;  // 1 stop bit
        serialParams.Parity = NOPARITY;      // No parity

        if (!SetCommState(portHandle, &serialParams)) {
            DWORD error = GetLastError();
            std::cerr << "Error setting serial port state. Error code: " << error << std::endl;
            return false;
        }

        return true;
    }

    void readData() {
        if (!isOpen()) {
            std::cerr << "Serial port is not open." << std::endl;
            return;
        }

        // Read data from the serial port
        const int bufferSize = 1024;
        char buffer[bufferSize];

        while (true) {
            DWORD bytesRead;
            if (ReadFile(portHandle, buffer, bufferSize, &bytesRead, NULL)) {
                // Process the received data here
                if (bytesRead > 0) {
                    std::cout.write(buffer, bytesRead);
                    std::cout.flush();
                }
            } else {
                DWORD error = GetLastError();
                std::cerr << "Error reading from serial port. Error code: " << error << std::endl;
                break;
            }
        }
    }

private:
    HANDLE portHandle;
};

class LoginManager {
public:
    LoginManager() {}

    bool authenticate() const {
        std::string username, password;

        std::cout << "Enter username: ";
        std::cin >> username;

        std::cout << "Enter password: ";
        std::cin >> password;

        // Replace this with your actual authentication logic
        return (username == "admin" && password == "password");
    }
};

int main() {
    // Create an instance of LoginManager
    LoginManager loginManager;

    // Keep looping until a successful login
    while (!loginManager.authenticate()) {
        std::cout << "Login failed. Access denied." << std::endl;
    }

    std::cout << "Login successful!" << std::endl;

    // Specify the COM port name (e.g., "COM1" or "COM2")
    const wchar_t* portName = L"\\\\.\\COM29";

    // Create an instance of SerialPort
    SerialPort serialPort(portName);

    // Check if the serial port is open
    if (serialPort.isOpen()) {
        // Set serial port parameters
        if (serialPort.setParams()) {
            // Run the serial port logic
            serialPort.readData();
        }
    }

    return 0;
}
