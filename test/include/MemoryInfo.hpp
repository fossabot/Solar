#ifndef SOLAR_MEMORYUSAGE_HPP
#define SOLAR_MEMORYUSAGE_HPP

#include <fstream>

class MemoryInfo
{
private:
    std::string str;
    int virtualMemory;
    int physicalMemory;

private:
    void trim_string(std::string &);

public:
    MemoryInfo() = default;
    MemoryInfo(const MemoryInfo &) = default;
    MemoryInfo &operator=(const MemoryInfo &) = default;
    MemoryInfo operator-(const MemoryInfo &);
    MemoryInfo &operator-=(const MemoryInfo &);
    MemoryInfo operator+(const MemoryInfo &);
    MemoryInfo &operator+=(const MemoryInfo &);
    void loadMemoryInformation();
    const std::string &toString();
    ~MemoryInfo() = default;
};

#endif
