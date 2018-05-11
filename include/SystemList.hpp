#ifndef SOLAR_SYSTEMLIST_HPP
#define SOLAR_SYSTEMLIST_HPP

#include <string>
#include <vector>

namespace Solar
{
    class SystemList
    {
    public:
        typedef std::string *iterator;
        typedef const std::string *const_iterator;

    private:
        std::vector<std::string> elements;

    private:
        void addElement(const std::string &);

    public:
        SystemList() = default;
        SystemList &operator=(const SystemList &);
        SystemList &operator+(const SystemList &);
        void operator+=(const SystemList &);
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        template<typename T>
        void add()
        {
            addElement(typeid(T).name());
        }

        virtual ~SystemList();
    };
}

#endif
