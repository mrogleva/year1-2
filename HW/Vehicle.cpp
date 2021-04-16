#include "Vehicle.hpp"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
{
    const MyString tempRegistration(registration);
    const MyString tempDescription(description);

    reg += tempRegistration;
    descript += tempDescription;
    spc = space;
}

const char* Vehicle::registration() const
{
    return reg.c_str();
}

const char* Vehicle::description() const
{
    return descript.c_str();
}

std::size_t Vehicle::space() const
{
    return spc;
}