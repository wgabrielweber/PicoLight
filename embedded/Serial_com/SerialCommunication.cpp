#include "SerialCommunication.hpp"
#include <stdio.h>
#include <tusb.h>

SerialCommunication::SerialCommunication() {
    stdio_init_all();
    while (!tud_cdc_connected()) {
        sleep_ms(100);
    }
    printf("tud_cdc_connected()\n");
    listening = false;        // Initialize the flag
    messageReceived = false;  // Initialize the flag
}

void SerialCommunication::startListening() {
    listening = true;  // Set the flag to start listening
    printf("reading\n");

    while (listening) {
        // Check to see if anything is available in the serial receive buffer
        while (tud_cdc_available()) {
            handleIncomingByte();

            // Debug message to indicate a byte is received
            printf("Received byte in loop.\n");

            // Exit the loop if a newline character is received
            if (messageReceived) {
                // Process the received message directly
                printf("Received Message: %s\n", message);

                // Reset the flags for the next message
                messageReceived = false;
                break;
            }
        }

        // Sleep for a short duration to avoid busy-waiting
        sleep_ms(10);
    }

    // Reset the messageReceived flag after checking it
    messageReceived = false;
}

std::string SerialCommunication::getReceivedMessage() const {
    return message;
}

void SerialCommunication::resetMessageReceived() {
    // ... (your implementation to reset the flags)
}

bool SerialCommunication::isMessageReceived() const {
    return messageReceived;
}

void SerialCommunication::stopListening() {
    listening = false;  // Set the flag to stop listening
}

void SerialCommunication::handleIncomingByte() {
    // Create a place to hold the incoming message
    static unsigned int message_pos = 0;

    // Read the next available byte in the serial receive buffer
    while (tud_cdc_available()) {
        char inByte;
        
        // Read the byte directly from the buffer
        if (tud_cdc_read(&inByte, 1) == 1) {
            // Debug: Print the received byte
            printf("Received byte: %c\n", inByte);

            // Message coming in (check not terminating character) and guard for over message size
            if (inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1)) {
                // Add the incoming byte to our message
                message[message_pos] = inByte;
                message_pos++;
            }

            // Newline character received or full message received...
            if (inByte == '\n' || message_pos == (MAX_MESSAGE_LENGTH - 1)) {
                // Add null character to string
                message[message_pos] = '\0';

                // Debug: Print the received message and its length
                //printf("Received message: %s, Length: %zu\n", message, strlen(message));

                // Check if the message is not empty
                if (message_pos > 0) {
                    messageReceived = true;
                    listening = false;  // Stop listening after a non-empty message is received
                }

                // Reset for the next message
                message_pos = 0;

                // Break to avoid processing additional incomplete messages
                break;
            }
        }
    }
}
