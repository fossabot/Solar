#include <iostream>
#include "BenchmarkResult.hpp"
#include "Movement.hpp"
#include "TestSystem.hpp"

static void test_over(unsigned int nbEntity)
{
    BenchmarkResult benchmarkResult(nbEntity);
    Solar::Core core;
    Solar::TimeIdx idx = {0, 0};
    auto scene = core.getPrimalWorld()->getDefaultScene();
    scene->add<Movement>();
    scene->add<TestSystem>();
    benchmarkResult.startAdding();
    for (unsigned int n = 0; n != nbEntity; ++n)
    {
        auto entity = core.createEntity("Entity");
        entity->add<Position>(0, 0);
        entity->add<Direction>(1, 1);
        entity->add<TestComponent>();
        scene->add(entity);
    }
    benchmarkResult.startUpdating();
    core.update(idx);
    benchmarkResult.endTest();
    std::cout << benchmarkResult << std::endl;
}

int main()
{
    test_over(10);
    std::cout << std::endl;
    test_over(100);
    std::cout << std::endl;
    test_over(1000);
    std::cout << std::endl;
    test_over(10000);
    std::cout << std::endl;
    test_over(100000);
    std::cout << std::endl;
    test_over(1000000);
    std::cout << std::endl;
    test_over(2000000);
    std::cout << std::endl;
    test_over(5000000);
    return 0;
}
