#ifndef SOLAR_ASCENEMANAGER_HPP
#define SOLAR_ASCENEMANAGER_HPP

#include <memory>
#include "TimeIdx.hpp"

namespace Solar
{
    class World;
    class AWorldScript
    {
        friend class World;
    private:
        void setWorld(const std::weak_ptr<World> &);

    protected:
        std::weak_ptr<World> world;

    protected:
        virtual void init();
        virtual void destroy();
        virtual ~AWorldScript() = default;
    };
}

#endif
