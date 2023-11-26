#include "serial_communication.hpp"

int main() {
    const char* portName = "\\\\.\\COM29";

    SerialCommunication serial(portName);

    if (!serial.Initialize()) {
        std::cerr << "Error initializing serial communication\n";
        return 1;
    }

    while (true) {
        const char* testMessage = "Hello, COM29!";
        serial.WriteToSerialPort(testMessage, strlen(testMessage));
        Sleep(1000); // Adjust the sleep duration as needed
    }

    return 0;
}
