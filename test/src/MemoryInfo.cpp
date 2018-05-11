#include <iostream>
#include "MemoryInfo.hpp"

void MemoryInfo::trim_string(std::string &str)
{
    size_t pos;
    while ((pos = str.find('\t', 0)) != std::string::npos)
        str.replace(pos, 1, " ");
    while ((pos = str.find("  ", 0)) != std::string::npos)
        str.replace(pos, 2, " ");
    if (str.find_first_of(' ') == 0)
        str = str.substr(1);
    if (str.find_last_of(' ') == str.length() - 1)
        str = str.substr(0, str.length() - 1);
}

void MemoryInfo::loadMemoryInformation()
{
    str = "";
    std::ifstream infile("/proc/self/status");
    std::string line, tmp;
    while (std::getline(infile, line))
    {
        if (line.find("VmSize:") == 0)
        {
            tmp = line.substr(8);
            trim_string(tmp);
            tmp = tmp.substr(0, tmp.length() - 3);
            virtualMemory = std::stoi(tmp);
        }
        else if (line.find("VmRSS:") == 0)
        {
            tmp = line.substr(7);
            trim_string(tmp);
            tmp = tmp.substr(0, tmp.length() - 3);
            physicalMemory = std::stoi(tmp);
        }
        //else
        //    std::cout << line << std::endl;
    }
}

MemoryInfo MemoryInfo::operator-(const MemoryInfo &other)
{
    MemoryInfo newInfo;
    newInfo.virtualMemory = this->virtualMemory - other.virtualMemory;
    newInfo.physicalMemory = this->physicalMemory - other.physicalMemory;
    return newInfo;
}

MemoryInfo &MemoryInfo::operator-=(const MemoryInfo &other)
{
    this->virtualMemory -= other.virtualMemory;
    this->physicalMemory -= other.physicalMemory;
    return *this;
}

MemoryInfo MemoryInfo::operator+(const MemoryInfo &other)
{
    MemoryInfo newInfo;
    newInfo.virtualMemory = this->virtualMemory + other.virtualMemory;
    newInfo.physicalMemory = this->physicalMemory + other.physicalMemory;
    return newInfo;
}

MemoryInfo &MemoryInfo::operator+=(const MemoryInfo &other)
{
    this->virtualMemory += other.virtualMemory;
    this->physicalMemory += other.physicalMemory;
    return *this;
}

const std::string &MemoryInfo::toString()
{
    if (str.empty())
    {
        str = "Virtual memory: ";
        str += std::to_string(virtualMemory);
        str += "ko. Physical memory: ";
        str += std::to_string(physicalMemory);
        str += "ko";
    }
    return str;
}
