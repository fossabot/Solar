#include "InnerCore.hpp"
#include "Entity.hpp"
#include "World.hpp"
#include "Scene.hpp"

Solar::Entity::Entity(const std::weak_ptr<InnerCore> &core, const std::string &id) : id(id), core(core), script(nullptr) {}

void Solar::Entity::setOwn(const std::weak_ptr<Entity> &own)
{
    this->own = own;
}

void Solar::Entity::init(const std::weak_ptr<Scene> &scene)
{
    auto oldScene = this->scene.lock();
    if (oldScene)
        oldScene->remove(own.lock());
    this->scene = scene;
}

void Solar::Entity::updateScene()
{
    auto ptr = scene.lock();
    if (ptr)
        ptr->update(own.lock());
}

bool Solar::Entity::find(const std::string &templateName)
{
    return (components.find(templateName) != components.end());
}

void Solar::Entity::setScript(const std::shared_ptr<AEntityScript> &script)
{
    script->setEntity(own);
    this->script = script;
}

const std::shared_ptr<Solar::AEntityScript> &Solar::Entity::getScript() const
{
    return script;
}

const std::string &Solar::Entity::getId() const
{
    return id;
}

void Solar::Entity::destroy()
{
    auto innerCore = core.lock();
    innerCore->destroy(own);
    components.clear();
    core.reset();
    scene.reset();
    if (script)
    {
        script->destroyEntity();
        script = nullptr;
    }
    own.reset();
}

const std::weak_ptr<Solar::Scene> &Solar::Entity::getScene() const
{
    return scene;
}

void Solar::Entity::setUid(Solar::Indexer::indexType uid)
{
    this->idx = uid;
}

Solar::Indexer::indexType Solar::Entity::getIdx() const
{
    return idx;
}
