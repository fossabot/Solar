#ifndef SOLAR_ASUBSCENEMANAGER_HPP
#define SOLAR_ASUBSCENEMANAGER_HPP

#include <memory>
#include "TimeIdx.hpp"
#include "System.hpp"

namespace Solar
{
    class Scene;
    class ASceneScript
    {
        friend class Scene;
    private:
        void setScene(const std::weak_ptr<Scene> &);

    protected:
        std::weak_ptr<Scene> scene;

    protected:
        virtual void receive(const System::Event &, const std::shared_ptr<Solar::Entity> &);
        virtual void receive(const System::Event &);
        virtual void init();
        virtual void destroy();
        virtual void update(const TimeIdx &);
        virtual ~ASceneScript() = default;
    };
}

#endif
