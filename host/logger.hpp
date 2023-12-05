 /**
 * @file logger.hpp
 * @brief logger header file
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 28/11/2023
 * @institution UFSC
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <vector>
#include <string>
#include <mutex>
#include <fstream>

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();

    void logMessage(const std::string& message);
    std::string popMessage();
    size_t popMessageCount();
    void writeToFile();
    void readFromFile();

private:
    std::vector<std::string> messageQueue;
    std::mutex mutex;
    std::ofstream outputFile;
    std::ifstream inputFile;
    std::string filename;
};

#endif // LOGGER_HPP