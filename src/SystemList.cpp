#include "SystemList.hpp"

Solar::SystemList::iterator Solar::SystemList::begin()
{
    return &elements[0];
}

Solar::SystemList::const_iterator Solar::SystemList::begin() const
{
    return &elements[0];
}

Solar::SystemList::iterator Solar::SystemList::end()
{
    return &elements[elements.size()];
}

Solar::SystemList::const_iterator Solar::SystemList::end() const
{
    return &elements[elements.size()];
}

void Solar::SystemList::addElement(const std::string &newElement)
{
    for (const auto &element : elements)
    {
        if (element == newElement)
            return;
    }
    elements.emplace_back(newElement);
}

Solar::SystemList &Solar::SystemList::operator=(const Solar::SystemList &other)
{
    elements = other.elements;
    return *this;
}

Solar::SystemList &Solar::SystemList::operator+(const Solar::SystemList &other)
{
    for (const auto &keys : other.elements)
        addElement(keys);
    return *this;
}

void Solar::SystemList::operator+=(const Solar::SystemList &other)
{
    for (const auto &keys : other.elements)
        addElement(keys);
}

Solar::SystemList::~SystemList()
{
    elements.clear();
    elements.shrink_to_fit();
}
