#ifndef VEHICLE_H
#define VEHICLE_H

#include "Organizer.hpp"

class Vehicle : public Registration
{
private:
    std::string description;
    Person* owner;
    
public:
    Vehicle(Registration registration, std::string description); 
    Vehicle(const Vehicle& other) = delete; 
    void operator=(const Vehicle& other) = delete; 

    void addOwner(Person* owner);
    void removeOwner();
};


#endif