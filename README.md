# SOLAR

The Solar is an ECS (Entity Component System) created by BrokenDollEntertainment<br>
The Solar is free to use
Here is a simple Hello World! example using the Solar:

main.cpp
```
#include <iostream>
#include <Core.hpp>

class Printable : public Solar::Component
{
private:
    std::string text;

public:
    Printable(const std::string &text) : text(text) {}

    const std::string &getText() const
    {
        return text;
    }
};

class Printer : public Solar::System
{
public:
    Printer()
    {
        include<Printable>();
    }

    void run(const Solar::TimeIdx &) override
    {
        for (const auto &entity : entities)
        {
            auto printable = entity->get<Printable>();
            if (printable)
                std::cout << printable->getText() << std::endl;
        }
    }
};

int main()
{
    Solar::Core core;
    Solar::TimeIdx idx = {0, 0};
    auto scene = core.getPrimalWorld()->getDefaultScene();
    scene->add<Printer>();
    auto entity = core.createEntity("Entity");
    entity->add<Printable>("Hello World!");
    scene->add(entity);
    core.update(idx);
    return 0;
}
```
You can compile this test like this<br>
````g++ main.cpp -o solarTest -lSolar````
