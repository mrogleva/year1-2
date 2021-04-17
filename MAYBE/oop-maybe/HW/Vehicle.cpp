#include "Vehicle.hpp"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
{
    MyString tempRegistration(registration);
    reg += tempRegistration;
    
    MyString tempDescription(description);
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