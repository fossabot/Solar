#include "BenchmarkResult.hpp"

BenchmarkResult::BenchmarkResult(unsigned int nbEntity) : nbEntity(nbEntity) {}

void BenchmarkResult::startAdding()
{
    beforeCreation.loadMemoryInformation();
    addingTime.startMeausre();
}

void BenchmarkResult::startUpdating()
{
    addingTime.stopMeasure();
    afterCreation.loadMemoryInformation();
    updatingTime.startMeausre();
}

void BenchmarkResult::endTest()
{
    updatingTime.stopMeasure();
}

std::ostream &operator<<(std::ostream &os, BenchmarkResult &result)
{
    os << "Test with " << result.nbEntity << " entities" << std::endl;
    os << "Adding of " << result.nbEntity << " entities: " << result.addingTime.toString() << std::endl;
    os << "Updating of " << result.nbEntity << " entities: " << result.updatingTime.toString() << std::endl;
    os << "Memory consumption:" << std::endl;
    os << (result.afterCreation - result.beforeCreation).toString();
    return os;
}
