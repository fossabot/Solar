#ifndef SOLAR_POSITION_HPP
#define SOLAR_POSITION_HPP

#include <Core.hpp>

class Position : public Solar::Component
{
public:
    int x;
    int y;

public:
    Position(int, int);
};

#endif
