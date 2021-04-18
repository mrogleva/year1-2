#include "Garage.hpp"

const std::size_t MAXALLOC = 100;

class VehicleAllocator 
{
private:
    Vehicle** adressBook;
    std::size_t index;

public:
    VehicleAllocator();
    ~VehicleAllocator(); 

    Vehicle* allocate(char* registration, char* description, std::size_t space);
};