#ifndef SOLAR_ENTITY_HPP
#define SOLAR_ENTITY_HPP

#include <unordered_map>
#include "AEntityScript.hpp"
#include "Component.hpp"
#include "Indexer.hpp"

namespace Solar
{
    class AEntityScript;
    class InnerCore;
    class Scene;
    class System;
    class Entity
    {
        friend class InnerCore;
        friend class Scene;
        friend class System;
    private:
        Solar::Indexer::indexType idx;
        std::string id;
        std::unordered_map<std::string, std::shared_ptr<Component>> components;
        std::weak_ptr<InnerCore> core;
        std::weak_ptr<Entity> own;
        std::weak_ptr<Scene> scene;
        std::shared_ptr<AEntityScript> script;

    private:
        Entity(const std::weak_ptr<InnerCore> &, const std::string &);
        void setUid(Indexer::indexType uid);
        void setOwn(const std::weak_ptr<Entity> &);
        void init(const std::weak_ptr<Scene> &);
        void updateScene();
        bool find(const std::string &);
        const std::weak_ptr<Scene> &getScene() const;

    public:
        Indexer::indexType getIdx() const;
        void destroy();
        const std::string &getId() const;
        void setScript(const std::shared_ptr<AEntityScript> &);
        const std::shared_ptr<AEntityScript> &getScript() const;

        template <typename T, typename... Args>
        void add(Args&&... args)
        {
            static_assert(std::is_base_of<Component, T>(), "Template given to add is not a valid component");
            std::shared_ptr<Component> component = std::make_shared<T>(std::forward<Args>(args)...);
            components[typeid(T).name()] = component;
            updateScene();
        }

        template<typename T>
        bool find()
        {
            return (components.find(typeid(T).name()) != components.end());
        }

        template<typename T>
        std::shared_ptr<T> get()
        {
            std::string templateName = typeid(T).name();
            if (components.find(templateName) != components.end())
                return std::dynamic_pointer_cast<T>(components[templateName]);
            return nullptr;
        }

        template<typename T>
        void remove()
        {
            if (components.find(typeid(T).name()) != components.end())
                updateScene();
        }
    };
}

#endif
