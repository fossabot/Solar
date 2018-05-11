#ifndef SOLAR_SUBSCENE_HPP
#define SOLAR_SUBSCENE_HPP

#include <string>
#include "System.hpp"
#include "TimeIdx.hpp"

namespace Solar
{
    class ASceneScript;
    class InnerCore;
    class World;
    /**
     * @brief Container of the System
     *
     * A Scene is a node in the Scene tree.<br>
     * To change the current Scene simply call Scene::goToScene(const std::string &name) on one of the current Scene with the name of one of his children<br>
     * When a Scene is updated (manually or through World::update), it update all his active System.<br>
     * To change the activity of a Scene in the World call Scene::setActivity or Scene::setActivityOf
     *
     * @see World
     */
    class Scene final
    {
        friend class Entity;
        friend class InnerCore;
        friend class System;
        friend class World;
    private:
        Indexer systemIndexer;
        bool active;
        std::shared_ptr<ASceneScript> script;
        std::string name;
        std::weak_ptr<World> world;
        std::weak_ptr<Scene> own;
        std::weak_ptr<Scene> mother;
        std::vector<std::weak_ptr<Scene>> childrens;
        Vector<System> activeSystem;
        std::unordered_map<std::string, std::vector<std::string>> systemToLink;
        std::unordered_map<std::string, std::shared_ptr<System>> systems;
        Vector<Entity> entities;

    private:
        Scene(const std::string &);
        void add(const std::shared_ptr<System> &, const SystemList & = SystemList());
        void setOwn(const std::weak_ptr<Scene> &);
        const std::weak_ptr<World> &getWorld() const;
        void setWorld(const std::weak_ptr<World> &world);
        void checkRemoveFrom(const std::shared_ptr<System> &, const std::shared_ptr<Entity> &);
        void checkAddTo(const std::shared_ptr<System> &, const std::shared_ptr<Entity> &);
        void checkUpdateIn(const std::shared_ptr<System> &, const std::shared_ptr<Entity> &);
        bool compare(const std::shared_ptr<Scene> &);
        bool compare(const std::string &);
        void add(const std::weak_ptr<Scene> &);
        void releaseMotherScene();
        void setMotherScene(const std::weak_ptr<Scene> &);
        void update(const std::shared_ptr<Entity> &);
        void load();
        void unload();
        void loaded();
        bool isInMotherWorld() const;
        void receive(const System::Event &, const std::shared_ptr<Solar::Entity> &);
        void receive(const System::Event &);
        const std::weak_ptr<Scene> &getMother() const;

    public:
        void optimizeFor(unsigned int);
        void setSceneScript(const std::shared_ptr<ASceneScript> &);
        void clear();
        bool add(const std::shared_ptr<Entity> &);
        void update(const TimeIdx &);
        const std::string &getName() const;
        void remove(const std::shared_ptr<Entity> &);
        void goToScene();
        void goToScene(const std::string &);
        void remove(const std::string &);
        void remove(const std::weak_ptr<Scene> &);
        bool isActive() const;
        void setActivityOf(const std::string &, bool);
        void setActivity(bool);

        template <typename T>
        bool remove()
        {
            if (systems.find(typeid(T).name()) == systems.end())
                return false;
            auto toRemove = systems[typeid(T).name()];
            systems.erase(typeid(T).name());
            unsigned int n = 0;
            for (const auto &system : systems)
                system.second->remove(toRemove);
            activeSystem.remove(toRemove);
            systemIndexer.free(toRemove->getIdx());
            return true;
        }

        template <typename T, const SystemList &list, typename... Args>
        void add(Args&&... args)
        {
            static_assert(std::is_base_of<System, T>(), "Template given to add is not a valid system");
            std::shared_ptr<System> system = std::make_shared<T>(std::forward<Args>(args)...);
            add(system, list);
        }

        template <typename T, typename... Args>
        void add(Args&&... args)
        {
            static_assert(std::is_base_of<System, T>(), "Template given to add is not a valid system");
            std::shared_ptr<System> system = std::make_shared<T>(std::forward<Args>(args)...);
            add(system, SystemList());
        }

        ~Scene();
    };
}

#endif
