#ifndef SOLAR_TIMEINFO_HPP
#define SOLAR_TIMEINFO_HPP

#include <chrono>
#include <string>

class TimeInfo
{
private:
    std::string str;
    long seconds;
    long milliseconds;
    long microseconds;
    long nanoseconds;
    std::chrono::time_point<std::chrono::system_clock> time;

public:
    TimeInfo() = default;
    TimeInfo(const TimeInfo &) = default;
    TimeInfo &operator=(const TimeInfo &) = default;
    void startMeausre();
    void stopMeasure();
    const std::string &toString();
    ~TimeInfo() = default;
};

#endif
