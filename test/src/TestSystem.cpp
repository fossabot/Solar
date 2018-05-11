#include "TestSystem.hpp"

TestSystem::TestSystem()
{
    include<TestComponent>();
}

void TestSystem::run(const Solar::TimeIdx &)
{
    for (const auto &entity : entities)
    {
        auto comflab = entity->get<TestComponent>();
        comflab->thingy *= 1.000001f;
        comflab->mingy = !comflab->mingy;
        comflab->dingy++;
    }
}