#include <iostream>
#include <windows.h>
#include <string>

#include "login_manager.hpp"
#include "serial_communication.hpp"

int main() {
    //Login Manager

    // Create an instance of LoginManager
    LoginManager loginManager;

    // Keep looping until a successful login
    while (!loginManager.authenticate()) {
        std::cout << "Login failed. Access denied." << std::endl;
    }

    std::cout << "Login successful!" << std::endl;

    //Serial Communication

    const char* portName = "\\\\.\\COM29";

    SerialCommunication serial(portName);

    if (!serial.Initialize()) {
        std::cerr << "Error initializing serial communication\n";
        return 1;
    }

    while (true) {
        const char* testMessage = "Hello, COM29!";
        serial.WriteToSerialPort(testMessage, strlen(testMessage));
        Sleep(1000); // Adjust the sleep duration as needed
    }

    return 0;
}
