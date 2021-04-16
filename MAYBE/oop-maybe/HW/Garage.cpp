#include "Garage.hpp"

Garage::Garage(std::size_t size)
{
    capacity = size;
    used = 0;
    index = 0;
    Vehicle** adressBook = new Vehicle*[capacity]; //if an exception is thrown, no object of type Garage is created
    //
}

Garage::~Garage()
{
    delete[] adressBook;
    adressBook = nullptr;
}

void Garage::insert(Vehicle& v)
{
    if(v.space() <= capacity - used)
    {
        for(std::size_t i = 0; i < index; ++i)
        {
            if(v.registration() == adressBook[i]->registration())
            {
                throw std::runtime_error("There is already a Vehicle with this registration in the Garage.");
            }
        }
        
        adressBook[index] = &v;
        index += 1;
        used += v.space();
    }
    else
    {
        throw std::runtime_error("There is no space for this Vehicle in the Garage.");
    }
}