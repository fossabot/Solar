#ifndef SOLAR_TESTSYSTEM_HPP
#define SOLAR_TESTSYSTEM_HPP

#include "TestComponent.hpp"

class TestSystem : public Solar::System
{
public:
    TestSystem();
    void run(const Solar::TimeIdx &) override;
};

#endif
