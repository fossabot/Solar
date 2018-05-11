#ifndef SOLAR_SCENE_HPP
#define SOLAR_SCENE_HPP

#include <string>
#include "System.hpp"
#include "TimeIdx.hpp"

namespace Solar
{
    class AWorldScript;
    class InnerCore;
    class Scene;
    /**
     * @brief Container of the Scene
     *
     * A World is a node in the World tree. The World tree first node is the default World in the Core (Core::getDefaultWorld)<br>
     * The default World is always considered active. There can be only one other active World, the current World.<br>
     * To change the current world simply call World::goToWorld(const std::string &name) on the current World with the name of one of his children or World::goToWorld() to set the upper node as the current World<br>
     * When a world is updated (manually or through Core::update), it update all his active Scene node.<br>
     *
     * @see Core
     */
    class World final
    {
        friend class InnerCore;
        friend class Scene;
    private:
        bool primal;
        size_t idx;
        std::weak_ptr<InnerCore> core;
        std::shared_ptr<AWorldScript> script;
        std::string name;
        std::weak_ptr<World> own;
        std::weak_ptr<World> mother;
        std::unordered_map<std::string, std::shared_ptr<World>> childrens;
        std::shared_ptr<Scene> defaultScene;
        std::vector<std::shared_ptr<Scene>> scenes;

    private:
        World(const std::weak_ptr<InnerCore> &, bool, const std::string &, size_t);
        size_t getIdx() const;
        bool isPrimal() const;
        const std::shared_ptr<Scene> getScene(const std::string &);
        void replaceSceneBy(const std::weak_ptr<Scene> &, const std::shared_ptr<Scene> &);
        void setOwn(const std::weak_ptr<World> &);
        bool compare(const std::string &);
        void releaseMother();
        void setMotherWorld(const std::weak_ptr<World> &);
        void load();
        void unload();

    public:
        /**
         * @brief Return the default Scene
         *
         * Return the Scene created at the World creation
         *
         * @return The default Scene of this World
         */
        const std::shared_ptr<Scene> &getDefaultScene() const;
        /**
         * @brief Set the script for this world
         *
         * Set the script for this world. The AWorldScript allow to add specific action to the update of the World
         *
         * @param script AWorldScript to set
         */
        void setWorldScript(const std::shared_ptr<AWorldScript> &script);
        /**
         * @brief Add a children to this World tree node
         *
         * Add the given world as a children to this World tree node
         *
         * @param world Children to add
         */
        void add(const std::shared_ptr<World> &world);
        /**
         * @brief Add a Scene node to this World
         *
         * Add the given Scene node as a "mother" Scene node to this World tree node
         *
         * @param world Children to add
         */
        void add(const std::shared_ptr<Scene> &);
        /**
         * @brief Update this World
         *
         * Update all the active Scene in this World
         *
         * @param idx TimeIdx for the update of the active Scene
         */
        void update(const TimeIdx &idx);
        /**
         * @brief Return the name
         *
         * Return the name of this World
         *
         * @return The name of this World
         */
        const std::string &getName() const;
        /**
         * @brief Set the current active World to the mother
         *
         * Set the current active World to mother of this World tree node
         */
        void goToWorld();
        /**
         * @brief Set the current active World by his name
         *
         * Set the current active World to one of the children from this World tree node which have the given name
         *
         * @param name Name of the World to switch
         */
        void goToWorld(const std::string &name);
        /**
         * @brief Remove a World by his name
         *
         * Remove the World from this World tree node which have the given name
         *
         * @param name Name of the World to remove
         */
        void remove(const std::string &name);
        /**
         * @brief Remove a World
         *
         * Remove the given World from this World tree node
         *
         * @param world World to remove
         */
        void remove(const std::shared_ptr<World> &world);
        /**
         * @brief Destructor
         *
         * Destroy the World
         */
        ~World();
    };
}

#endif
