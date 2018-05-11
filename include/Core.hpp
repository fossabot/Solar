#ifndef SOLAR_CORE_HPP
#define SOLAR_CORE_HPP

#include "InnerCore.hpp"

/**
 * @namespace Solar
 *
 * General namespace containing all the ECS
 */
namespace Solar
{
    /**
     * @brief ECS Core
     *
     * First thing to create to use the ECS<br>
     * The Core allow to:<br>
     * - Create a new Entity<br>
     * - Create a new Scene<br>
     * - Create a new World<br>
     * - Update the current World and the primal World
     */
    class Core
    {
    private:
        static std::shared_ptr<InnerCore> core;
        static unsigned int instance;

    public:
        /**
         * @brief Constructor
         *
         * Allow to create an instance of the ECS Core
         *
         * @warning The core use a singleton pattern, so instanciate a new Core will kept the data from the old one
         */
        Core();

        /**
         * @brief Access to the primal world
         *
         * Allow to use the primal world by granting access to it. The primal world will always be active and be updated last
         *
         * @return The primal world
         */
        const std::shared_ptr<World> &getPrimalWorld() const;
        /**
         * @brief Create an Entity
         *
         * Create a new Entity with the given name
         *
         * @param name Name of the Entity
         * @return The freshly created Entity
         */
        std::shared_ptr<Entity> createEntity(const std::string &name) const;
        /**
         * @brief Create a World
         *
         * Create a new World with the given name
         *
         * @param name Name of the World
         * @return The freshly created World
         */
        std::shared_ptr<World> createWorld(const std::string &name) const;
        /**
         * @brief Create a Scene
         *
         * Create a new Scene with the given name
         *
         * @param name Name of the Scene
         * @return The freshly created Scene
         */
        std::shared_ptr<Scene> createScene(const std::string &name) const;
        /**
         * @brief Update the ECS
         *
         * Update the current world the the primal world with the given TimeIdx
         *
         * @param idx TimeIdx
         */
        void update(const TimeIdx &idx);
        /**
         * @brief Destructor
         *
         * Destroy the Core and free all memory
         *
         * @warning Destroy the Core only if it is the last Core instance
         */
        ~Core();
    };
}

#endif
