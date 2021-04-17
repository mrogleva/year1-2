#include "Garage.hpp"

Garage::Garage(std::size_t size)
{ 
    Vehicle** adressBook = new Vehicle*[size]; //if an exception is thrown, no object of type Garage is created
    //
    capacity = size;
    used = 0;
    index = 0;
    std::cout<<"A garage with capacity "<<capacity<<" was created.\n";
}

Garage& Garage::operator=(const Garage& rhs)
{
    if(capacity >= rhs.size())
    {
        clear();
        for(std::size_t i = 0; i<rhs.size(); ++i)
        {
            *adressBook[i] = rhs.at(i);
        }
    }
    else
    {
        throw std::runtime_error("The copy cannot be done because there isn't enough space.");
    }
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
        std::cout<<"The Vehicle was added\n";
    }
    else
    {
        throw std::runtime_error("There is not enough space for this Vehicle in the Garage.");
    }
}

void Garage::erase(const char* registration)
{
    MyString reg(registration);
    bool erased = false;
    for(std::size_t i = 0; i < index-1; ++i)
        {
            if(reg == adressBook[i]->registration())
            {
                used -= adressBook[i]->space();
                adressBook[i] = adressBook[--index];
                erased = true;
                std::cout<<"The Vehicle was erased\n";
                break;               
            }
        }
    if(reg == adressBook[index-1]->registration())
    {
        used -= adressBook[index-1]->space();
        adressBook[index-1] = nullptr;
        erased = true;
        std::cout<<"The Vehicle was erased\n";
    }
    if(erased == false)
    {
        std::cout<<"There is no Vehicle with that registration in the Garage.\n";
    }
}

const Vehicle& Garage::at(std::size_t pos) const
{
    if(pos<index)
    {
        return *adressBook[pos];
    }
    else
    {
        throw std::out_of_range("There is no Vehicle at that position.");
    }
}

const Vehicle& Garage::operator[](std::size_t pos) const
{
    //Функцията да не прави проверка за коректност дали pos е валидна позиция.
    return *adressBook[pos]; 
}

bool Garage::empty() const
{
    if(used == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::size_t Garage::size() const
{
    return used;
}

void Garage::clear()
{
    for(std::size_t i = 0; i < index; ++i)
    {
        adressBook[i] = nullptr;
    }
    used = 0;
    index = 0;
}

const Vehicle* Garage::find(const char* registration) const
{
    MyString reg(registration);
    for(std::size_t i = 0; i < index; ++i)
    {
        if(reg == adressBook[i]->registration())
        {
            return adressBook[i];     
        }
    }
}