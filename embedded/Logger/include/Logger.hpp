/**
 * @file Logger.hpp
 * @brief Logger class for logging the embedded system data
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 21/11/2023
 * @institution UFSC
 */

/* 
 *  Logger
 */


#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>
#include <string>
#include <cstdarg>

class Node {
public:
    std::string logMessage;
    Node* next;

    Node(const std::string& message);
};

class Logger {
private:
    Node* front;
    Node* rear;

public:
    Logger();
    void log(const char* format, ...);
    std::string dequeue();
    ~Logger();
};

#endif /* LOGGER_HPP_ */
