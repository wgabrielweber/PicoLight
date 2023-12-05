 /**
 * @file dade_time_provider.cpp
 * @brief date_time_provider implementation file
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 28/11/2023
 * @institution UFSC
 */

#include "date_time_provider.hpp"

std::string DateTimeProvider::getCurrentTime() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // Format the time in ISO 8601 format
    std::tm tm_time = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm_time, "%Y%m%d%H%M%S");

    return oss.str();
}
