#include "AEntityScript.hpp"

void Solar::AEntityScript::setEntity(const std::weak_ptr<Entity> &entity)
{
    this->entity = entity;
}

void Solar::AEntityScript::destroyEntity()
{
    entity.reset();
}