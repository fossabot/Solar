#ifndef SOLAR_SYSTEM_HPP
#define SOLAR_SYSTEM_HPP

#include <vector>
#include <memory>
#include "Vector.hpp"
#include "SystemList.hpp"
#include "TimeIdx.hpp"

namespace Solar
{
    class Scene;
    class System
    {
        friend class Scene;
    private:
        Indexer::indexType idx;
        std::weak_ptr<Scene> scene;
        std::vector<std::string> includeList;
        std::vector<std::string> excludeList;
        SystemList internalList;
        std::vector<std::shared_ptr<System>> systems;

    protected:
        Vector<Entity> entities;

    public:
        class Event
        {
            friend class System;
        private:
            std::string type;

        private:
            template <typename T>
            void set()
            {
                type = typeid(T).name();
            }

        public:
            template <typename T>
            bool is() const
            {
                return (typeid(T).name() == type);
            }
        };

    private:
        void clear();
        void addIn(const std::shared_ptr<Entity> &);
        void add(const std::shared_ptr<System> &);
        void remove(const std::shared_ptr<System> &);
        void removeFrom(const std::shared_ptr<Entity> &);
        bool isIn(const std::shared_ptr<Entity> &);
        const SystemList &getInternalList() const;
        void setScene(const std::weak_ptr<Scene> &, Indexer::indexType);
        void signal(const Event &, const std::shared_ptr<Entity> &);
        void signal(const Event &);

    protected:
        virtual bool isCompatible(const std::shared_ptr<Entity> &);
        virtual void run(const TimeIdx &) = 0;
        virtual void add(const std::shared_ptr<Entity> &);
        virtual void remove(const std::shared_ptr<Entity> &);
        virtual void receive(const Event &, const std::shared_ptr<Solar::Entity> &);
        virtual void receive(const Event &);

        template<typename T>
        void signal(const std::shared_ptr<Entity> &entity)
        {
            Event event;
            event.set<T>();
            signal(event, entity);
        }

        template<typename T>
        void signal()
        {
            Event event;
            event.set<T>();
            signal(event);
        }

        template <typename T>
        void link()
        {
            internalList.add<T>();
        }

        template <typename T>
        void include()
        {
            includeList.emplace_back(typeid(T).name());
        }

        template <typename T>
        void exclude()
        {
            excludeList.emplace_back(typeid(T).name());
        }

    public:
        Indexer::indexType getIdx() const;
        virtual ~System();
    };
}

#endif
