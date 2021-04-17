#include "VehAlloc.hpp"

VehicleAllocator::VehicleAllocator()
{
    adressBook = new Vehicle*[MAXALLOC]; 
    index = 0;
}

VehicleAllocator::~VehicleAllocator()
{
    for(std::size_t i = 0; i<index; ++i)
    {
        delete adressBook[i];
    }
    delete[] adressBook;
    adressBook = nullptr;
}

Vehicle* VehicleAllocator::allocate(char* registration, char* description, std::size_t space)
{
    if(index<MAXALLOC)
    {
        adressBook[index] = new Vehicle(registration, description, space);
        index+=1;
        return adressBook[index-1];
    }
    else 
    {
        throw std::runtime_error("You have registered too many vehicles.");
    }
}