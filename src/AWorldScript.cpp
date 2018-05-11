#include "AWorldScript.hpp"
#include "World.hpp"

void Solar::AWorldScript::setWorld(const std::weak_ptr<World> &world)
{
    this->world = world;
}

void Solar::AWorldScript::init() {}
void Solar::AWorldScript::destroy() {}