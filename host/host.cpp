#include <iostream>
#include <windows.h>
#include <string>

#include "login_manager.hpp"
#include "serial_communication.hpp"
#include "date_time_provider.hpp"

//Login Manager
void Login() {


    // Create an instance of LoginManager
    LoginManager loginManager;

    // Keep looping until a successful login
    while (!loginManager.authenticate()) {
        std::cout << "Login failed. Access denied." << std::endl;
    }

    std::cout << "Login successful!" << std::endl;
}



int main() {

    Login();
    
//Serial Communication

    const char* portName = "\\\\.\\COM29";

    SerialCommunication serial(portName);

    if (!serial.Initialize()) {
        std::cerr << "Error initializing serial communication\n";
        return 1;
    }
    
    // Writing loop
    while (true) {

        std::string currentTime = DateTimeProvider::getCurrentTime();
        std::cout << "Current time and date (ISO 8601 format): " << currentTime << std::endl;
        std::cout << "dataSentFlag: " << serial.dataSentFlag << ", errorFlag: " << serial.errorFlag << std::endl;

        const char* message = currentTime.c_str();
        serial.WriteToSerialPort(message, static_cast<DWORD>(currentTime.size()));

        serial.dataSentFlag = true;

        if (serial.dataSentFlag == true && serial.errorFlag == true) {
            std::cerr << "Error writing to serial port. Exiting program." << std::endl;
            break;
        }

        Sleep(1000); // Adjust the sleep duration as needed
    }

    // Reading loop
    while (true) {
        serial.ReadFromSerialPort();
        std::cout << "reading" << std::endl;
        
        Sleep(10000); // Adjust the sleep duration as needed
    }

    return 0;
}