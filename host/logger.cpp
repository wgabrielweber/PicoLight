 /**
 * @file logger.cpp
 * @brief logger implementation file
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 28/11/2023
 * @institution UFSC
 */

#include "logger.hpp"
#include <fstream>
#include <iostream>

Logger::Logger(const std::string& filename) : filename(filename) {
    // Open the file for both reading and writing
    outputFile.open(filename, std::ios::app);
    inputFile.open(filename);
}

Logger::~Logger() {
    // Close the file handles
    outputFile.close();
    inputFile.close();
}

void Logger::logMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    messageQueue.push_back(message);
}

std::string Logger::popMessage() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!messageQueue.empty()) {
        std::string frontMessage = messageQueue.front();
        messageQueue.erase(messageQueue.begin());
        return frontMessage;
    } else {
        return ""; // Return an empty string if the queue is empty
    }
}

size_t Logger::popMessageCount() {
    std::lock_guard<std::mutex> lock(mutex);
    return messageQueue.size();
}

void Logger::writeToFile() {
    
    std::lock_guard<std::mutex> lock(mutex);
    std::ofstream outputFile(filename, std::ios::app);  // Open the file in append mode

    if (outputFile.is_open()) {
        // Check if the file is empty
        outputFile.seekp(0, std::ios::end);
        // Check if the file is empty, and if so, write the header
        if (outputFile.tellp() == 0) {
            outputFile << "=== Ambient Light Controller Logger ===\n";
            outputFile << "\nTimestamp | Luminance [lux] | Brightness | Active Time Since Initialization [seconds]\n";
        }

        // std::cout << "File opened successfully for writing: " << filename << std::endl;
        
        for (const auto& message : messageQueue) {
            outputFile << message;
        }
        outputFile.flush();

        messageQueue.clear(); // Clear the queue after writing to the file
    } else {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
    }
}

void Logger::readFromFile() {
    std::lock_guard<std::mutex> lock(mutex);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << "Read from file: " << line;
        }
        inputFile.clear(); // Clear any error flags
        inputFile.seekg(0, std::ios::beg); // Reset file position to the beginning
    } else {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
    }
}