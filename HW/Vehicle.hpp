#include "MyString.hpp"

#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle 
{
private:
    MyString reg; 
    MyString descript;
    std::size_t spc;

public:
    Vehicle(const char* registration, const char* description, std::size_t space); ///Constructor

    const char* registration() const; ///Връща регистрационния номер като C-style символен низ.
    const char* description() const; ///Връща описанието на превозното средство като C-style символен низ.
    std::size_t space() const; ///Връща мястото, което заема превозното средство при паркиране.
};


#endif