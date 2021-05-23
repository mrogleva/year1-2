#ifndef PERSON_H
#define PERSON_H

#include "Vehicle.hpp"
#include <vector>

class Person
{
private:
    std::string name;
    unsigned int id; //make sure it is not 0!
    std::vector<Vehicle*> vehicles;
    
public:
    Person(std::string name, unsigned int id); //по същество не е проблем ако се случи да се създаде извън класа 
    //Organizer, защото така или иначе неговите методи търсят само в неговата си база данни. Все пак аз не предвиждам да 
    //се създават обекти извън Organizer //na gornoto nivo proverka za id! 
    Person(const Person& other);
    ~Person();

    std::string getName() const;
    unsigned getId() const;
    std::size_t numberOfVehicles() const;
    Vehicle* getVehicle(std::size_t pos) const; // !doesn't return a pointer to prevent unwanted changes to the object

    bool addVehicle(Vehicle& veh); //bez proverki tuk; na gornoto nivo! //добавя КОПИЕ във вектора на person //vryshta dali e bilo usp
    bool releaseVehicle(Registration registration); //първо проверява дали има такова във вектора /връща дали операцията е 
                                                    //била успешна (т.к. се борави с копията, самото vehicle не спира да съществ)

};


#endif