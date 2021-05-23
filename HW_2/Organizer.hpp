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
    void addVehicle(std::string registration, std::string description); //should check if the reg is taken!
    void addPerson(std::string name, unsigned int id); //should check if the id is taken before adding the person!
    void aquire(unsigned int id, std::string registration); //griji se za Vehicle i Person 
    void release(unsigned int id, std::string registration); //griji se za Vehicle i Person
    
    void remove(unsigned int id); //removes a person 
    void remove(std::string registration); //removes a vehicle //NA GORNOTO NIVO да се иска потвържд от потребителя
    
    //The following functions are used only for the unit tests:
    unsigned getPersonId(std::size_t pos) const;
    std::string getVehicleReg(std::size_t pos) const;
    Person* getPerson(unsigned id);
    Vehicle getVehicle(std::string registration);
};

#endif


    //Ако се опитва да се премахне кола, която има собственик или собственик, 
    // който притежава коли, да се изведе съобщение и да се попита потребителят дали 
    // е сигурен. Ако той потвърди, обектът да се изтрие, но да се коригират останалите, 
    // които са свързани с него.