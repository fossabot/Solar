#ifndef SOLAR_MOVEMENT_HPP
#define SOLAR_MOVEMENT_HPP

#include "Direction.hpp"
#include "Position.hpp"

class Movement : public Solar::System
{
public:
    Movement();
    void run(const Solar::TimeIdx &) override;
};

#endif
