#include "Movement.hpp"

Movement::Movement()
{
    include<Position>();
    include<Direction>();
}

void Movement::run(const Solar::TimeIdx &idx)
{
    for (const auto &entity : entities)
    {
        auto position = entity->get<Position>();
        auto direction = entity->get<Direction>();
        position->x += direction->x * idx.real;
        position->y += direction->y * idx.real;
    }
}