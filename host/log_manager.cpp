// log_manager.cpp
#include "log_manager.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

LogManager::LogManager(const std::string& filename) : filename("log.txt") {
}

LogManager::~LogManager() {
}

void LogManager::readAndStoreData() {
    std::ifstream inputFile("log.txt");

    if (inputFile.is_open()) {
        std::string line;
        int lineCount = 0;

        // Read and ignore the first three lines (headers)
        while (lineCount < 3 && std::getline(inputFile, line)) {
            lineCount++;
        }

        // Read and store the rest of the lines
        while (std::getline(inputFile, line)) {
            storedData.push_back(line);
        }

        inputFile.close();
    } else {
        std::cerr << "Error opening file for reading: " << "log.txt" << std::endl;
    }
}

void LogManager::printStoreData() {     // for debugging
    for (const auto& data : storedData) {
        std::cout << data << std::endl;
    }
}

void LogManager::writeStoredData(const std::string& outputFilename) {
    std::ofstream outputFile(outputFilename);

    if (outputFile.is_open()) {
        // Write the stored data to the output file
        for (const auto& data : storedData) {
            outputFile << data << std::endl;
        }

        std::cout << "\nData written to " << outputFilename << std::endl;  // Optional: Print a success message

        outputFile.close();
    } else {
        std::cerr << "Error opening file for writing: " << outputFilename << std::endl;
    }
}

void LogManager::filteredTimestamp(const std::string& initialTimestamp, const std::string& endTimestamp) {
    // Read the log entries from the file
    std::ifstream inputFile("log.txt");

    if (inputFile.is_open()) {
        std::string line;
        std::vector<std::string> filteredData;

        // Read and ignore the first three lines (headers)
        for (int i = 0; i < 3 && std::getline(inputFile, line); ++i);

        // Read and store the rest of the lines within the specified timestamp range
        while (std::getline(inputFile, line)) {
            if (line.compare(0, initialTimestamp.size(), initialTimestamp) >= 0 &&
                line.compare(0, endTimestamp.size(), endTimestamp) <= 0) {
                filteredData.push_back(line);
            }
        }

        // Update storedData with the filtered data
        storedData = std::move(filteredData);

        inputFile.close();
    } else {
        std::cerr << "Error opening file for reading: " << "log.txt" << std::endl;
    }
}
