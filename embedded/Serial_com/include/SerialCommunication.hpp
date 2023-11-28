#ifndef SERIAL_COMMUNICATION_HPP
#define SERIAL_COMMUNICATION_HPP

#include <string>
#include "pico/stdlib.h"

#define MAX_MESSAGE_LENGTH 15
#define TIMEOUT_MS 3000  // Timeout in milliseconds

class SerialCommunication {
public:
    SerialCommunication();

    void startListening();
    void stopListening();
    bool isMessageReceived() const;
    std::string getReceivedMessage() const;
    void resetMessageReceived();

private:
    void handleIncomingByte();
    
    char message[MAX_MESSAGE_LENGTH];
    char incomingByte;            // Variable to store the incoming byte
    bool listening;               // Flag to control the listening loop
    bool messageReceived;         // Flag to indicate if a message has been received
    std::string receivedMessage;  // Member to store the received message
};

#endif // SERIAL_COMMUNICATION_HPP