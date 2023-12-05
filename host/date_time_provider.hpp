 /**
 * @file dade_time_provider.hpp
 * @brief date_time_provider header file
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 28/11/2023
 * @institution UFSC
 */

#ifndef DATE_TIME_PROVIDER_HPP
#define DATE_TIME_PROVIDER_HPP

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

class DateTimeProvider {
public:
    static std::string getCurrentTime();
};

#endif // DATE_TIME_PROVIDER_HPP
