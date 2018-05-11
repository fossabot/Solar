#ifndef SOLAR_INNERCORE_HPP
#define SOLAR_INNERCORE_HPP

#include "Entity.hpp"
#include "Indexer.hpp"
#include "World.hpp"
#include "Scene.hpp"

namespace Solar
{
    class Core;
    /**
     * @brief Class used by the Core
     *
     * Private class used by the Core to manage the ECS
     */
    class InnerCore final
    {
        friend class Core;
        friend class Entity;
        friend class World;
    private:
        Indexer indexer;
        std::weak_ptr<InnerCore> own;
        std::shared_ptr<World> primalWorld;
        std::shared_ptr<World> currentWorld;
        std::vector<std::shared_ptr<World>> worlds;
        std::vector<std::shared_ptr<Scene>> scenes;

    private:
        InnerCore() = default;
        void setCurrentWorld(const std::weak_ptr<World> &);
        const std::shared_ptr<World> &getPrimalWorld() const;
        void setOwn(const std::weak_ptr<InnerCore> &);
        std::shared_ptr<Entity> createEntity(const std::string &);
        std::shared_ptr<World> createWorld(const std::string &);
        std::shared_ptr<Scene> createScene(const std::string &);
        void update(const TimeIdx &);
        void destroy(const std::weak_ptr<Entity> &);

    public:
        /**
         * @brief Destructor
         *
         * Destroy the InnerCore and clear his memory
         */
        ~InnerCore();
    };
}

#endif
