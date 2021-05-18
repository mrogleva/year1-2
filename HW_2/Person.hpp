#ifndef PERSON_H
#define PERSON_H

#include "Organizer.hpp"

class Person
{
private:
    std::string name;
    unsigned int id;
    std::vector<Vehicle> vehicles;
    
public:
    Person(std::string name, unsigned int id); //по същество не е проблем ако се случи да се създаде извън класа 
    //Organizer, защото така или иначе неговите методи търсят само в неговата си база данни. Все пак аз не предвиждам да 
    //се създават обекти извън Organizer

    Person(const Person& other) = delete; 
    void operator=(const Person& other) = delete; 

    std::string getName();
    unsigned getId();
    std::size_t numberOfVehicles();
    Vehicle getVehicle(std::size_t pos);

    void addVehicle(Vehicle& veh); //bez proverki tuk - борави с вектора на person
    void releaseVehicle(Registration registration); //проверява дали има такова във вектора

};


#endif