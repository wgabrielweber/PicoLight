/**
 * @file Logger.cpp
 * @brief Implementation of the Logger class for logging the embedded system data
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */

/* 
 *  Logger
 */

#include "Logger.hpp"

Node::Node(const std::string& message) : logMessage(message), next(nullptr) {}

Logger::Logger() : front(nullptr), rear(nullptr) {}

void Logger::log(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[256];  // Adjust the buffer size as needed
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    Node* newNode = new Node(buffer);

    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    
    // Increment the log count
    logCount++;

    // Check if the maximum log limit is reached
    if (logCount > MAX_LOGS) {
        // Dequeue logs until the log count is within the limit
        while (logCount > MAX_LOGS) {
            dequeue();
        }
    }
}

std::string Logger::dequeue() {
    if (front == nullptr) {
        return "";  // Returning an empty string if the log queue is empty
    }

    Node* temp = front;
    std::string message = temp->logMessage;

    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;

    // Decrement the log count
    logCount--;

    return message;
}

Logger::~Logger() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    rear = nullptr;
    logCount = 0;
}