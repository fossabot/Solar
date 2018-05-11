#include "World.hpp"
#include "Scene.hpp"
#include "ASceneScript.hpp"

Solar::Scene::Scene(const std::string &name) :
        active(true),
        script(nullptr),
        name(name) {}

void Solar::Scene::optimizeFor(unsigned int size)
{
    entities.optimizeFor(size);
}

bool Solar::Scene::isInMotherWorld() const
{
    bool primal = world.lock()->isPrimal();
    return primal;
}

void Solar::Scene::setSceneScript(const std::shared_ptr<ASceneScript> &script)
{
    script->setScene(own);
    bool primal = world.lock()->isPrimal();
    if (primal)
        script->init();
    this->script = script;
}

void Solar::Scene::update(const TimeIdx &timeIdx)
{
    for (const auto &system : activeSystem)
        system->run(timeIdx);
    if (script)
        script->update(timeIdx);
}

const std::string &Solar::Scene::getName() const
{
    return name;
}

bool Solar::Scene::compare(const std::shared_ptr<Scene> &scene)
{
    return (scene->name == this->name);
}

bool Solar::Scene::compare(const std::string &name)
{
    return (name == this->name);
}

void Solar::Scene::add(const std::weak_ptr<Scene> &scene)
{
    auto newChild = scene.lock();
    auto newChildWorld = newChild->getWorld().lock();
    if (newChildWorld && newChildWorld != world.lock())
        return ;
    else if (!newChildWorld)
        newChild->setWorld(world);
    if (newChild->getMother().lock() == own.lock())
        return;
    newChild->setMotherScene(own);
    childrens.push_back(scene);
}

void Solar::Scene::setMotherScene(const std::weak_ptr<Scene> &scene)
{
    mother = scene;
}

void Solar::Scene::checkAddTo(const std::shared_ptr<System> &system, const std::shared_ptr<Entity> &entity)
{
    if (!system || !entity)
        return ;
    if (system->isCompatible(entity))
        system->addIn(entity);
}

void Solar::Scene::checkRemoveFrom(const std::shared_ptr<System> &system, const std::shared_ptr<Entity> &entity)
{
    if (!system || !entity)
        return ;
    if (system->isIn(entity))
        system->removeFrom(entity);
}

void Solar::Scene::checkUpdateIn(const std::shared_ptr<System> &system, const std::shared_ptr<Entity> &entity)
{
    if (!system || !entity)
        return ;
    if (system->isCompatible(entity) && !system->isIn(entity))
        system->addIn(entity);
    else if (!system->isCompatible(entity) && system->isIn(entity))
        system->removeFrom(entity);
}

void Solar::Scene::loaded()
{
    for (const auto &entity : entities)
    {
        for (const auto &system : systems)
            checkAddTo(system.second, entity);
    }
}

bool Solar::Scene::add(const std::shared_ptr<Entity> &toAdd)
{
    if (toAdd->getScene().lock() == own.lock())
        return false;
    toAdd->init(own);
    entities.add(toAdd);
    for (const auto &system : systems)
        checkAddTo(system.second, toAdd);
    return true;
}

void Solar::Scene::add(const std::shared_ptr<System> &toAdd, const SystemList &list)
{
    if (systems.find(typeid(*toAdd).name()) != systems.end())
        return;
    toAdd->setScene(own, systemIndexer.next());
    SystemList systemList = toAdd->getInternalList();
    systemList += list;
    for (const auto &key : systemList)
    {
        if (systems.find(key) != systems.end())
            toAdd->add(systems[key]);
        else
        {
            if (systemToLink.find(key) == systemToLink.end())
                systemToLink[key] = std::vector<std::string>();
            systemToLink[key].emplace_back(typeid(*toAdd).name());
        }
    }
    if (systemToLink.find(typeid(*toAdd).name()) != systemToLink.end())
    {
        for (const auto &toLink : systemToLink[typeid(*toAdd).name()])
            systems[toLink]->add(toAdd);
    }
    systems[typeid(*toAdd).name()] = toAdd;
    activeSystem.add(toAdd);
    for (const auto &entity : entities)
        checkAddTo(toAdd, entity);
}

void Solar::Scene::remove(const std::shared_ptr<Entity> &toRemove)
{
    for (const auto &system : systems)
        checkRemoveFrom(system.second, toRemove);
    entities.remove(toRemove);
}

void Solar::Scene::update(const std::shared_ptr<Entity> &entity)
{
    for (const auto &system : systems)
        checkUpdateIn(system.second, entity);
}

void Solar::Scene::goToScene()
{
    auto up = mother.lock();
    if (!up)
        return;
    unload();
    if (!up->isInMotherWorld())
        up->load();
    world.lock()->replaceSceneBy(own, mother.lock());
}

void Solar::Scene::goToScene(const std::string &name)
{
    for (const auto &children : childrens)
    {
        auto child = children.lock();
        if (child->compare(name))
        {
            unload();
            child->load();
            world.lock()->replaceSceneBy(own, child);
            return;
        }
    }
}

void Solar::Scene::load()
{
    bool primal = world.lock()->isPrimal();
    if (primal)
        return;
    if (script)
        script->init();
}

void Solar::Scene::unload()
{
    bool primal = world.lock()->isPrimal();
    if (primal)
        return;
    if (script)
        script->destroy();
}

void Solar::Scene::clear()
{
    for (const auto &system : systems)
        system.second->clear();
    systems.clear();
    activeSystem.clear();
    entities.clear();
}

void Solar::Scene::remove(const std::string &name)
{
    unsigned int n = 0;
    for (const auto &children : childrens)
    {
        auto child = children.lock();
        if (child->getName() == name)
        {
            child->releaseMotherScene();
            childrens.erase(childrens.begin() + n);
            return;
        }
        ++n;
    }
}

void Solar::Scene::remove(const std::weak_ptr<Scene> &scene)
{
    unsigned int n = 0;
    auto toRemove = scene.lock();
    for (const auto &children : childrens)
    {
        auto child = children.lock();
        if (child == toRemove)
        {
            child->releaseMotherScene();
            childrens.erase(childrens.begin() + n);
            return;
        }
        ++n;
    }
}

void Solar::Scene::setOwn(const std::weak_ptr<Solar::Scene> &own)
{
    this->own = own;
}

bool Solar::Scene::isActive() const
{
    return active;
}

void Solar::Scene::setActivity(bool active)
{
    this->active = active;
}

void Solar::Scene::setActivityOf(const std::string &name, bool active)
{
    auto scene = world.lock()->getScene(name);
    if (scene)
        scene->setActivity(active);
}

void Solar::Scene::releaseMotherScene()
{
    mother.reset();
}

void Solar::Scene::receive(const Solar::System::Event &event, const std::shared_ptr<Solar::Entity> &entity)
{
    if (script)
        script->receive(event, entity);
}

void Solar::Scene::receive(const Solar::System::Event &event)
{
    if (script)
        script->receive(event);
}

const std::weak_ptr<Solar::World> &Solar::Scene::getWorld() const
{
    return world;
}

void Solar::Scene::setWorld(const std::weak_ptr<Solar::World> &world)
{
    this->world = world;
    for (const auto &children : childrens)
        children.lock()->setWorld(world);
}

const std::weak_ptr<Solar::Scene> &Solar::Scene::getMother() const
{
    return mother;
}

Solar::Scene::~Scene()
{
    childrens.clear();
    childrens.shrink_to_fit();
    activeSystem.clear();
    systemToLink.clear();
    systems.clear();
    if (script != nullptr)
        script.reset();
    world.reset();
    own.reset();
    mother.reset();
}
