#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "Person.hpp"

class Organizer //singleton
{
private:
    std::vector<Person> people; 
    std::vector<Vehicle> vehicles; 

    Organizer(); 
    
public:
    Organizer(const Organizer& other) = delete;
    void operator=(const Organizer& other) = delete;
    static Organizer& getInstance();

    //проверки тук!
    void addPerson(Person& person); //should check if the id is taken before adding a person!
    void addVehicle(Registration registration, std::string description); //should check if the reg is taken!
    void release(unsigned int id, Registration registration); //griji se za Vehicle i Person
    void aquire(unsigned int id, Registration registration); //griji se za Vehicle i Person
    
    void remove(unsigned int id); //raboti s vector people
    friend void remove(Registration registration); //raboti s vector vehicles
    //Ако се опитва да се премахне кола, която има собственик или собственик, 
    // който притежава коли, да се изведе съобщение и да се попита потребителят дали 
    // е сигурен. Ако той потвърди, обектът да се изтрие, но да се коригират останалите, 
    // които са свързани с него.

};



#endif