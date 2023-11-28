/**
 * @file PicoRTC.cpp
 * @brief New time and date formats for the original SDK functions
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */

#include "PicoRTC.hpp"
#include <cstdio>
#include <cstring>

void new_datetime_str(char *result, size_t size, const char *datetime_str) {
    int year, month, day, hour, minute, second;
    char month_str[20];

    // Print the received datetime_str for debugging
    printf("Received datetime_str: %s\n", datetime_str);

    // Adjusted format string for sscanf
    int parsed_values = sscanf(datetime_str, "%*s %d %*s %s %d %d:%d:%d",
                               &day, month_str, &year, &hour, &minute, &second);

    // Print the parsed values for debugging
    printf("Parsed values: Year: %d, Month: %s, Day: %d, Hour: %d, Minute: %d, Second: %d\n",
           year, month_str, day, hour, minute, second);

    // Convert month string to number
    if (strcmp(month_str, "January") == 0) month = 1;
    else if (strcmp(month_str, "February") == 0) month = 2;
    // Add other months as needed...

    // Format the result string in the desired format
    snprintf(result, size, "Year: %d, Month: %02d, Day: %02d, Hour: %02d, Minute: %02d, Second: %02d",
             year, month, day, hour, minute, second);
}
