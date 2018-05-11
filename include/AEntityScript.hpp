#ifndef SOLAR_AENTITYMANAGER_HPP
#define SOLAR_AENTITYMANAGER_HPP

#include <memory>
#include "TimeIdx.hpp"

namespace Solar
{
    class Entity;
    class World;
    /**
     * Class allowing to specify some action of the Entity
     *
     */
    class AEntityScript
    {
        friend class Entity;
    protected:
        std::weak_ptr<Entity> entity;

    private:
        void setEntity(const std::weak_ptr<Entity> &);
        void destroyEntity();

    public:
        virtual ~AEntityScript() = default;
    };
}

#endif
