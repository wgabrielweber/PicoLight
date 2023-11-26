#include <iostream>
#include <windows.h>

#define MAX_MESSAGE_LENGTH 20

int main()
{
    HANDLE serialHandle;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};

    // Open the serial port
    serialHandle = CreateFileA("\\\\.\\COM29", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (serialHandle == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error opening serial port\n";
        return 1;
    }

    // Set serial parameters
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(serialHandle, &dcbSerialParams))
    {
        std::cerr << "Error getting serial port state\n";
        CloseHandle(serialHandle);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_115200;  // Update baud rate
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(serialHandle, &dcbSerialParams))
    {
        std::cerr << "Error setting serial port state\n";
        CloseHandle(serialHandle);
        return 1;
    }

    // Set timeouts
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(serialHandle, &timeouts))
    {
        std::cerr << "Error setting timeouts\n";
        CloseHandle(serialHandle);
        return 1;
    }

    // Main loop
    while (true)
    {
        // Check if data is available to read
        DWORD bytesRead;
        char inByte;

        if (ReadFile(serialHandle, &inByte, 1, &bytesRead, NULL))
        {
            if (bytesRead > 0)
            {
                // Handle the incoming byte
                std::cout << inByte;
            }
        }
        else
        {
            std::cerr << "Error reading from serial port\n";
            break;
        }

        // Send data to serial port (replace this with your test data)
        const char *testData = "Test data from Windows";
        DWORD bytesWritten;

        if (WriteFile(serialHandle, testData, strlen(testData), &bytesWritten, NULL))
        {
            if (bytesWritten > 0)
            {
                std::cout << "Data sent to serial port\n";
            }
        }
        else
        {
            std::cerr << "Error writing to serial port\n";
            break;
        }

        Sleep(100); // Adjust the sleep duration as needed
    }

    // Close the serial port
    CloseHandle(serialHandle);

    return 0;
}
