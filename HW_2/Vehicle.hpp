#ifndef VEHICLE_H
#define VEHICLE_H

#include "Registration.hpp"

class Person;

class Vehicle : public Registration
{
private:
    std::string description;
    unsigned int ownerId; 
    
public:
    Vehicle(Registration registration, std::string description); 
    Vehicle(const Vehicle& other);

    std::string getDescription() const;
    unsigned int getOwnerId() const; //can be used to find the owner, better than passing a pointer, as this way the class stays encapsulated
    void addOwner(unsigned int owner);
    void removeOwner();
};


#endif