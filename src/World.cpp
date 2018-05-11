#include "AWorldScript.hpp"
#include "InnerCore.hpp"
#include "World.hpp"
#include "Scene.hpp"

Solar::World::World(const std::weak_ptr<InnerCore> &core, bool primal, const std::string &name, size_t idx) :
        primal(primal),
        idx(idx),
        core(core),
        script(nullptr),
        name(name)
{
    defaultScene = std::shared_ptr<Scene>(new Scene(name));
    defaultScene->setOwn(defaultScene);
}

const std::shared_ptr<Solar::Scene> Solar::World::getScene(const std::string &name)
{
    for (const auto &subScene : scenes)
    {
        if (subScene->compare(name))
            return subScene;
    }
    return nullptr;
}

void Solar::World::setWorldScript(const std::shared_ptr<AWorldScript> &script)
{
    script->setWorld(own);
    if (primal)
        script->init();
    this->script = script;
}

void Solar::World::replaceSceneBy(const std::weak_ptr<Solar::Scene> &scene, const std::shared_ptr<Solar::Scene> &with)
{
    auto toReplace = scene.lock();
    if (toReplace == defaultScene)
        return;
    for (unsigned int n = 0; n != scenes.size(); ++n)
    {
        if (scenes[n] = toReplace)
        {
            scenes[n] = with;
            return;
        }
    }
}

void Solar::World::update(const TimeIdx &timeIdx)
{
    if (defaultScene->isActive())
        defaultScene->update(timeIdx);
    for (const auto &scene : scenes)
    {
        if (scene->isActive())
            scene->update(timeIdx);
    }
}


const std::string &Solar::World::getName() const
{
    return name;
}

bool Solar::World::compare(const std::string &name)
{
    return (name == this->name);
}

void Solar::World::add(const std::shared_ptr<World> &world)
{
    if (childrens.find(world->getName()) == childrens.end())
        childrens[world->getName()] = world;
}

void Solar::World::releaseMother()
{
    mother.reset();
}

void Solar::World::setMotherWorld(const std::weak_ptr<World> &scene)
{
    mother = scene;
}

void Solar::World::add(const std::shared_ptr<Scene> &toAdd)
{
    if (toAdd == defaultScene)
        return;
    auto sceneWorld = toAdd->getWorld().lock();
    if (sceneWorld && sceneWorld != own.lock())
        return;
    else if (!sceneWorld)
        toAdd->setWorld(own);
    for (const auto &subScene : scenes)
    {
        if (subScene == toAdd)
            return;
    }
    scenes.emplace_back(toAdd);
}

void Solar::World::goToWorld()
{
    unload();
    auto up = mother.lock();
    if (!up->primal)
    {
        up->load();
        auto manager = core.lock();
        manager->setCurrentWorld(mother);
    }
}

void Solar::World::goToWorld(const std::string &name)
{
    if (childrens.find(name) != childrens.end())
    {
        auto children = childrens[name];
        children->load();
        auto manager = core.lock();
        manager->setCurrentWorld(children);
    }
}

void Solar::World::load()
{
    if (primal)
        return;
    if (script)
        script->init();
    defaultScene->load();
    for (const auto &scene : scenes)
        scene->load();
}

void Solar::World::unload()
{
    if (primal)
        return;
    if (script)
        script->destroy();
    defaultScene->unload();
    for (const auto &scene : scenes)
        scene->unload();
}

void Solar::World::remove(const std::string &name)
{
    if (childrens.find(name) != childrens.end())
    {
        auto children = childrens[name];
        children->releaseMother();
        childrens.erase(name);
    }
}

void Solar::World::remove(const std::shared_ptr<World> &world)
{
    remove(world->getName());
}

void Solar::World::setOwn(const std::weak_ptr<Solar::World> &own)
{
    this->own = own;
    defaultScene->setWorld(own);
}

bool Solar::World::isPrimal() const
{
    return primal;
}

size_t Solar::World::getIdx() const
{
    return idx;
}

const std::shared_ptr<Solar::Scene> &Solar::World::getDefaultScene() const
{
    return defaultScene;
}

Solar::World::~World()
{
    core.reset();
    if (script != nullptr)
        script.reset();
    own.reset();
    mother.reset();
    childrens.clear();
    defaultScene.reset();
    scenes.clear();
    scenes.shrink_to_fit();
}
