#include "SerialCommunication.hpp"
#include <stdio.h>

int main() {
    SerialCommunication serialCommunication;

    while (true) {
        serialCommunication.startListening();

        // Perform any necessary actions after each listening cycle
        printf("Listening cycle complete. Performing other actions...\n");

        // Sleep for a while before starting listening again
        sleep_ms(5000);  // Sleep for 5 seconds, adjust as needed
    }

    return 0;
}