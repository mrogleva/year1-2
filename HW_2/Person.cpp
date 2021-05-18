#include "Person.hpp"

Person::Person(std::string name, unsigned int id)
{
    this->name = name;
    this->id = id;
}

std::string Person::getName()
{
    return name;
}

unsigned Person::getId()
{
    return id;
}

std::size_t Person::numberOfVehicles()
{
    return vehicles.size();
}

