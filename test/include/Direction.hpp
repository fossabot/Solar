#ifndef SOLAR_DIRECTION_HPP
#define SOLAR_DIRECTION_HPP

#include <Core.hpp>

class Direction : public Solar::Component
{
public:
    int x;
    int y;

public:
    Direction(int, int);
};

#endif
