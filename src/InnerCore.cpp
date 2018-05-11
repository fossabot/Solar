#include "InnerCore.hpp"

void Solar::InnerCore::setOwn(const std::weak_ptr<InnerCore> &own)
{
    this->own = own;
    primalWorld = std::shared_ptr<World>(new World(own, true, "primal", worlds.size()));
    primalWorld->setOwn(primalWorld);
    worlds.emplace_back(primalWorld);
}

std::shared_ptr<Solar::Entity> Solar::InnerCore::createEntity(const std::string &name)
{
    auto entity = std::shared_ptr<Entity>(new Entity(own, name));
    entity->setOwn(entity);
    entity->setUid(indexer.next());
    return entity;
}

std::shared_ptr<Solar::World> Solar::InnerCore::createWorld(const std::string &name)
{
    auto world = std::shared_ptr<World>(new World(own, false, name, worlds.size()));
    world->setOwn(world);
    worlds.emplace_back(world);
    return world;
}

std::shared_ptr<Solar::Scene> Solar::InnerCore::createScene(const std::string &name)
{
    auto scene = std::shared_ptr<Scene>(new Scene(name));
    scene->setOwn(scene);
    scenes.emplace_back(scene);
    return scene;
}

void Solar::InnerCore::update(const TimeIdx &timeIdx)
{
    if (currentWorld)
        currentWorld->update(timeIdx);
    primalWorld->update(timeIdx);
}

const std::shared_ptr<Solar::World> &Solar::InnerCore::getPrimalWorld() const
{
    return primalWorld;
}

void Solar::InnerCore::setCurrentWorld(const std::weak_ptr<World> &newCurrentWorld)
{
    auto newCurrent = newCurrentWorld.lock();
    if (newCurrent->getIdx() == 0)
        return;
    currentWorld = worlds[newCurrent->getIdx()];
}

void Solar::InnerCore::destroy(const std::weak_ptr<Solar::Entity> &entity)
{
    auto toDestroy = entity.lock();
    indexer.free(toDestroy->getIdx());
    for (const auto &scene : scenes)
        scene->remove(toDestroy);
}

Solar::InnerCore::~InnerCore()
{
    own.reset();
    primalWorld.reset();
    if (currentWorld != nullptr)
        currentWorld.reset();
    worlds.clear();
    worlds.shrink_to_fit();
    scenes.clear();
    scenes.shrink_to_fit();
}
