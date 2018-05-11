#ifndef SOLAR_ENTITYVECTOR_HPP
#define SOLAR_ENTITYVECTOR_HPP

#include <vector>
#include "Entity.hpp"

namespace Solar
{
    class Scene;
    class System;
    template <typename T>
    class Vector final
    {
        friend class Scene;
        friend class System;
    public:
        typedef std::shared_ptr<T> *iterator;
        typedef const std::shared_ptr<T> *const_iterator;

    private:
        unsigned long size;
        std::vector<std::shared_ptr<T>> items;

    private:
        Vector() : size(0) {}

        void optimizeFor(unsigned int size)
        {
            items.reserve(size);
        }

        int getPos(const std::shared_ptr<T> &item)
        {
            int left = 0;
            auto right = static_cast<int>(size - 1);
            if (item->getIdx() < items[0]->getIdx() || item->getIdx() > items[right]->getIdx())
                return -1;
            while ((items[left]->getIdx() != items[right]->getIdx()) && (item->getIdx() > items[left]->getIdx()) && (item->getIdx() < items[right]->getIdx()))
            {
                auto pos = static_cast<int>(left + ((right - left) * ((item->getIdx() - items[left]->getIdx()) / (items[right]->getIdx() - items[left]->getIdx()))));
                if (items[pos]->getIdx() == item->getIdx())
                    return pos;
                else if(items[pos]->getIdx() < item->getIdx())
                    left = pos + 1;
                else
                    right = pos - 1;
            }
            if (items[left]->getIdx() == item->getIdx())
                return left;
            return -1;
        }
        void insert(const std::shared_ptr<T> &item, int pos)
        {
            items.insert(items.begin() + pos, item);
            ++size;
        }

    public:
        bool add(const std::shared_ptr<T> &item)
        {
            if (size == 0)
            {
                insert(item, static_cast<int>(size));
                return true;
            }
            int left = 0;
            auto right = static_cast<int>(size - 1);
            if (item->getIdx() < items[0]->getIdx())
            {
                insert(item, 0);
                return true;
            }
            else if (item->getIdx() > items[right]->getIdx())
            {
                insert(item, static_cast<int>(size));
                return true;
            }
            while ((items[left] != items[right]) && (item > items[left]) && (item < items[right]))
            {
                auto pos = static_cast<int>(left + ((right - left) * ((item->getIdx() - items[left]->getIdx()) / (items[right]->getIdx() - items[left]->getIdx()))));
                if (items[pos]->getIdx() == item->getIdx())
                    return false;
                else if(items[pos]->getIdx() < item->getIdx())
                    left = pos + 1;
                else
                    right = pos - 1;
            }
            if (items[left]->getIdx() == item->getIdx())
                return false;
            if (items[left]->getIdx() > item->getIdx())
                insert(item, left);
            else if (items[right]->getIdx() < item->getIdx())
                insert(item, right + 1);
            return true;
        }

        bool remove(const std::shared_ptr<T> &item)
        {
            int pos = getPos(item);
            if (pos != -1)
            {
                items.erase(items.begin() + pos);
                --size;
                return true;
            }
            return false;
        }

        bool find(const std::shared_ptr<T> &item)
        {
            return (getPos(item) != -1);
        }

        void clear()
        {
            size = 0;
            items.clear();
            items.shrink_to_fit();
        }

        iterator begin()
        {
            return &items[0];
        }

        const_iterator begin() const
        {
            return &items[0];
        }

        iterator end()
        {
            return &items[size];
        }

        const_iterator end() const
        {
            return &items[size];
        }

        ~Vector()
        {
            items.clear();
            items.shrink_to_fit();
        }
    };
}

#endif
