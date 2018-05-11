#ifndef SOLAR_BENCHMARKRESULT_HPP
#define SOLAR_BENCHMARKRESULT_HPP

#include <ostream>
#include "MemoryInfo.hpp"
#include "TimeInfo.hpp"

class BenchmarkResult
{
private:
    unsigned int nbEntity;
    MemoryInfo beforeCreation;
    MemoryInfo afterCreation;
    TimeInfo addingTime;
    TimeInfo updatingTime;

public:
    explicit BenchmarkResult(unsigned int nbEntity);
    BenchmarkResult(const BenchmarkResult &) = default;
    BenchmarkResult &operator=(const BenchmarkResult &) = default;
    void startAdding();
    void startUpdating();
    void endTest();
    friend std::ostream &operator<<(std::ostream &os, BenchmarkResult &result);
};

#endif
