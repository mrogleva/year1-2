#include "Organizer.hpp"

Organizer::Organizer()
{
}

Organizer& Organizer::getInstance() 
{
    static Organizer instance;
    return instance;
}

void Organizer::addVehicle(std::string registration, std::string description) //try catch
{
    Registration reg(registration); //could throw
    for(std::size_t i = 0; i<vehicles.size(); ++i) 
    {
        if(vehicles[i].getReg() == reg.getReg()) //could throw
        {
            throw std::runtime_error("A vehicle with that registration already exists.");
        }
    }
    Vehicle temp(reg, description);
    vehicles.push_back(temp);
    if(vehicles.back().getReg() != temp.getReg())   //could throw
    {
        throw std::runtime_error("Memory error. Nothing was added.");
    }
}

void Organizer::addPerson(std::string name, unsigned int id)   //try catch
{
    if(id > 0) //0 is not a valid ID
    {
        for(std::size_t i = 0; i<people.size(); ++i) 
        {
            if(people[i].getId() == id) //could throw
            {
                throw std::runtime_error("A person with that ID already exists.");
            }
        }
        Person temp(name, id);
        people.push_back(temp);
    }
    else
    {
        throw std::runtime_error("Invalid ID.");
    }
}

void Organizer::aquire(unsigned int id, Registration registration)
{
    std::size_t p = 0;
    bool flagP = 0;

    std::size_t v = 0;
    bool flagV = 0;

    while(p < people.size() && !flagP)
    {
        if(people[p].getId() == id)
        {
            flagP = 1;
        }
        if(!flagP)
        {
            ++p;
        }
    }
    while(v < vehicles.size() && !flagV)
    {
        if(vehicles[v].getReg() == registration.getReg())
        {
            flagV = 1;
        }
        if(!flagV)
        {
            ++v;
        }
    }
    if(!flagP && !flagV)
    {
        throw std::runtime_error("There are no such vehicle and person.");
    }
    if(!flagP)
    {
        throw std::runtime_error("This person does not exist.");
    }
    if(!flagV)
    {
        throw std::runtime_error("This vehicle does not exist.");
    }

    vehicles[v].addOwner(id);
    people[p].addVehicle(vehicles[v]);
}


void Organizer::release(unsigned int id, Registration registration)
{
    bool flag = 0;
    for(std::size_t i = 0; i<people.size(); ++i)
    {
        if(people[i].getId() == id)
        {
            if(people[i].releaseVehicle(registration))
            {
                for(std::size_t j = 0; j<vehicles.size(); ++j)
                {
                    if(vehicles[j].getReg() == registration.getReg())
                    {
                        vehicles[j].removeOwner();
                        flag = 1;
                        break;
                    }
                }
            }
            else
            {
                throw std::runtime_error("This person does not own this vehicle.");
            }
        }
    }
    if(!flag)
    {
        throw std::runtime_error("This person does not exist.");
    }
}