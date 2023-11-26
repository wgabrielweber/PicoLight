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
