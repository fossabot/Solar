#include <iostream>
#include "Core.hpp"

std::shared_ptr<Solar::InnerCore> Solar::Core::core = nullptr;
unsigned int Solar::Core::instance = 0;

Solar::Core::Core()
{
    if (!core)
    {
        core = std::shared_ptr<InnerCore>(new InnerCore());
        core->setOwn(core);
    }
    ++instance;
}

const std::shared_ptr<Solar::World> &Solar::Core::getPrimalWorld() const
{
    return core->getPrimalWorld();
}

std::shared_ptr<Solar::Entity> Solar::Core::createEntity(const std::string &name) const
{
    return core->createEntity(name);
}

std::shared_ptr<Solar::World> Solar::Core::createWorld(const std::string &name) const
{
    return core->createWorld(name);
}

std::shared_ptr<Solar::Scene> Solar::Core::createScene(const std::string &name) const
{
    return core->createScene(name);
}

void Solar::Core::update(const Solar::TimeIdx &timeIdx)
{
    core->update(timeIdx);
}

Solar::Core::~Core()
{
    --instance;
    if (instance == 0)
        core.reset();
}
