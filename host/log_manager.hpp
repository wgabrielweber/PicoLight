// log_manager.hpp
#ifndef LOG_MANAGER_HPP
#define LOG_MANAGER_HPP

#include <vector>
#include <string>
#include <fstream>

class LogManager {
public:
    LogManager(const std::string& filename);
    ~LogManager();

    void readAndStoreData();
    void printStoreData();
    void writeStoredData(const std::string& outputFilename);
    // Filter stored data based on timestamp range
    void filteredTimestamp(const std::string& initialTimestamp, const std::string& endTimestamp);

private:
    std::vector<std::string> storedData;
    std::string filename;
};

#endif // LOG_MANAGER_HPP