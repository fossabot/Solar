#include "TimeInfo.hpp"

void TimeInfo::startMeausre()
{
    time = std::chrono::system_clock::now();
}

void TimeInfo::stopMeasure()
{
    str = "";
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    seconds = std::chrono::duration_cast<std::chrono::seconds>(end - time).count();
    milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - time).count() % 1000;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - time).count() % 1000;
    nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - time).count() % 1000;
}

const std::string &TimeInfo::toString()
{
    if (str.empty())
    {
        str = std::to_string(seconds);
        str += 's';
        str += std::to_string(milliseconds);
        str += "ms";
        str += std::to_string(microseconds);
        str += "µs";
        str += std::to_string(nanoseconds);
        str += "ns";
    }
    return str;
}
