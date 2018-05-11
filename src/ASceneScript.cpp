#include "ASceneScript.hpp"
#include "Scene.hpp"

void Solar::ASceneScript::setScene(const std::weak_ptr<Scene> &scene)
{
    this->scene = scene;
}

void Solar::ASceneScript::receive(const Solar::System::Event &, const std::shared_ptr<Solar::Entity> &) {}
void Solar::ASceneScript::receive(const Solar::System::Event &) {}
void Solar::ASceneScript::init() {}
void Solar::ASceneScript::destroy() {}
void Solar::ASceneScript::update(const TimeIdx &) {}