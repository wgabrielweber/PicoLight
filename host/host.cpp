 /**
 * @file host.cpp
 * @brief Main file of the host system
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 04/12/2023
 * @institution UFSC
 */

/* 
 *  Host System Main File
 */

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <future>
#include <chrono>
#include <iomanip>

#include "login_manager.hpp"
#include "date_time_provider.hpp"
#include "serial_communication.hpp"
#include "logger.hpp"
#include "log_manager.hpp"

// Global Constants
const std::string LOG_FILE_NAME = "log.txt";
const std::string NEW_LOG_FILE_NAME = "new_log.txt";

//Login Manager
void Login() {
   
    LoginManager loginManager;

    // Keep looping until a successful login
    while (!loginManager.authenticate()) {
        std::cout << "Login failed. Access denied." << std::endl;
    }

    std::cout << "Login successful!" << std::endl;
}

void readLog(SerialCommunication& serial, Logger& logger) {
    while (true) {
        serial.ReadFromSerialPort(logger);

        // Check for errors during reading
        if (serial.errorFlag) {
            std::cerr << "Error during reading. Exiting reading loop.\n";
            break;
        }

        // Store the logged messages to the txt file and clean the logger
        if (logger.popMessageCount() >= 10) {
            // Write logged messages to a text file
            logger.writeToFile();

            std::vector<std::string> receivedMessages;

            while (true) {
                std::string receivedMessage = logger.popMessage();
                if (receivedMessage.empty()) {
                    break;
                }
                std::cout << receivedMessage;

                // Store receivedMessage into a vector
                receivedMessages.push_back(receivedMessage);
            }
        }
        // Introduce a delay between iterations
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Adjust the interval as needed
    }
}

// Function to handle user log management
void manageUserLog(LogManager& logManager) {
    // ... Your existing logic for user log management
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
    
// Writing loop (initialize the Pico RTC)
    while (true) {

        std::string currentTime = DateTimeProvider::getCurrentTime();

        const char* message = currentTime.c_str();
        serial.WriteToSerialPort(message, static_cast<DWORD>(currentTime.size()));

        serial.dataSentFlag = true;

        Sleep(10);

        if (serial.dataSentFlag == true && serial.errorFlag == true) {
            std::cerr << "Timestamp sent. Exiting writing loop." << std::endl;
            break;
        }
    }

    serial.dataSentFlag = false;
    serial.errorFlag = false;

    CloseHandle(serial.serialHandle);

    Sleep(500);

    // Reinitialize for reading
    if (!serial.Initialize()) {
        std::cerr << "Error reinitializing serial communication for reading\n";
        return 1;
    }

    Logger logger(LOG_FILE_NAME);
    LogManager logManager(NEW_LOG_FILE_NAME);

    // Create a future for readLog function
    auto future = std::async(std::launch::async, readLog, std::ref(serial), std::ref(logger));

    // Loop for user logging management
    while(1) {
        
        // Read and store data from the log file using LogManager
        logManager.readAndStoreData();

        std::string initialTimestamp, endTimestamp;
        char newFile;

        std::cout << "\n-----      Logger Manager      -----" << std::endl;
        std::cout << "Timestamp Format YYYY-MM-DDTHH:MM:SS" << std::endl;
        
        // Validate and get the initial timestamp
        while (true) {
            std::cout << "\nInitial Timestamp: ";
            std::cin >> initialTimestamp;

            if (initialTimestamp.size() == 19) {
                break; // Exit the loop if the timestamp is valid
            }

            std::cout << "Invalid timestamp. Please enter in the correct format." << std::endl;
        }    

       // Validate and get the end timestamp
        while (true) {
            std::cout << "End Timestamp: ";
            std::cin >> endTimestamp;

            if (endTimestamp.size() == 19) {
                break; // Exit the loop if the timestamp is valid
            }

            std::cout << "Invalid timestamp. Please enter in the correct format." << std::endl;
        }

        // Filter data based on timestamps
        logManager.filteredTimestamp(initialTimestamp, endTimestamp);

        // Write filtered data to a new file
        logManager.writeStoredData("new_log.txt");

        // Prompt user for further action
        std::cout << "\nDo you want to create a new file? [Y/N]" << std::endl;
        std::cin >> newFile;

        // Convert input to uppercase for case-insensitive comparison
        newFile = std::toupper(newFile);

        if (newFile == 'N') {
            std::cout << "Exiting the program" << std::endl;
            std::cout << "PicoLight running with embedded logger only" << std::endl;
            Sleep(5000);
            
            // Close the serial port handle after reading
            CloseHandle(serial.serialHandle);

            return 0;
        } else if (newFile != 'Y') {
            std::cout << "Wrong input. Enter Y to create a new file or N to continue logging." << std::endl;
        }
    }    // End of Loop for user logging management

    // Wait for the readLog to finish (this line is optional, depends on your application logic)
    future.wait();

}   // End of main