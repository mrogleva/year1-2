#include "Vehicle.hpp"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
{
    try
    {
        const MyString tempRegistration(registration);
        reg += tempRegistration;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() <<"Unable to allocate memory 1\n";
        throw;
    }
    try
    {
        const MyString tempDescription(description);
        descript += tempDescription;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() <<"Unable to allocate memory 2\n";
        throw;
    }
    
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