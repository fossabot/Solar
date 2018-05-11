#include <iostream>
#include "Scene.hpp"
#include "System.hpp"

void Solar::System::addIn(const std::shared_ptr<Entity> &entity)
{
    entities.add(entity);
    add(entity);
}

void Solar::System::remove(const std::shared_ptr<System> &toRemove)
{
    unsigned int n = 0;
    for (const auto &system : systems)
    {
        if (system == toRemove)
        {
            systems.erase(systems.begin() + n);
            return;
        }
        ++n;
    }
}

void Solar::System::add(const std::shared_ptr<System> &toAdd)
{
    for (const auto &system : systems)
    {
        if (system == toAdd)
            return;
    }
    systems.emplace_back(toAdd);
}

void Solar::System::removeFrom(const std::shared_ptr<Entity> &toRemove)
{
    if (entities.remove(toRemove))
        remove(toRemove);
}

bool Solar::System::isIn(const std::shared_ptr<Entity> &toFind)
{
    return entities.find(toFind);
}

const Solar::SystemList &Solar::System::getInternalList() const
{
    return internalList;
}

void Solar::System::clear()
{
    entities.clear();
}

bool Solar::System::isCompatible(const std::shared_ptr<Entity> &entity)
{
    for (const auto &it : excludeList)
    {
        if (entity->find(it))
            return false;
    }
    for (const auto &it : includeList)
    {
        if (!entity->find(it))
            return false;
    }
    return true;
}

void Solar::System::setScene(const std::weak_ptr<Solar::Scene> &scene, Indexer::indexType idx)
{
    this->idx = idx;
    this->scene = scene;
}

void Solar::System::signal(const Solar::System::Event &event, const std::shared_ptr<Solar::Entity> &entity)
{
    scene.lock()->receive(event, entity);
    for (const auto &system : systems)
    {
        if (system->isIn(entity))
            system->receive(event, entity);
    }
}

void Solar::System::signal(const Solar::System::Event &event)
{
    scene.lock()->receive(event);
    for (const auto &system : systems)
        system->receive(event);
}

void Solar::System::add(const std::shared_ptr<Entity> &) {}
void Solar::System::remove(const std::shared_ptr<Entity> &) {}
void Solar::System::receive(const Event &, const std::shared_ptr<Entity> &) {}
void Solar::System::receive(const Event &) {}

Solar::System::~System()
{
    scene.reset();
    includeList.clear();
    includeList.shrink_to_fit();
    excludeList.clear();
    excludeList.shrink_to_fit();
    systems.clear();
    systems.shrink_to_fit();
}

Solar::Indexer::indexType Solar::System::getIdx() const
{
    return idx;
}
