#ifndef SOLAR_TESTCOMPONENT_HPP
#define SOLAR_TESTCOMPONENT_HPP

#include <Core.hpp>

class TestComponent : public Solar::Component
{
public:
    double thingy;
    int dingy;
    bool mingy;

public:
    TestComponent();
};

#endif
