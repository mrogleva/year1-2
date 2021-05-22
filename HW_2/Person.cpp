#include "Person.hpp"

Person::Person(std::string name, unsigned int id)
{
    this->name = name;
    this->id = id;
}

std::string Person::getName() const
{
    return name;
}

unsigned Person::getId() const
{
    return id;
}

std::size_t Person::numberOfVehicles() const
{
    return vehicles.size();
}

Registration Person::getVehicle(std::size_t pos) const
{
    if(pos<vehicles.size())
    {
        return vehicles[pos];
    }
    else
    {
        throw std::out_of_range("Out of range");
    }
}

bool Person::addVehicle(Vehicle& veh)
{
    vehicles.push_back(veh);
    if(vehicles.back().getReg() == veh.getReg())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Person::releaseVehicle(Registration registration)
{
    for(std::size_t i = 0; i<vehicles.size(); ++i)
    {
        if(vehicles[i].getReg() == registration.getReg())
        {
            vehicles.erase(vehicles.begin()+i);
            return true;
        }
    }
    return false;
}