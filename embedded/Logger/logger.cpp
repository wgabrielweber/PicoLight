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

    return message;
}

Logger::~Logger() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    rear = nullptr;
}