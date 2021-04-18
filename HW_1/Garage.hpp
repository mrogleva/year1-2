#include "Vehicle.hpp"

#ifndef GARAGE_H
#define GARAGE_H

class Garage
{
private:
    std::size_t capacity; ///How many parking cells exist in the garage; 
    std::size_t used;     ///How many parking cells are currently occupied
    Vehicle** adressBook; ///pointer to the array, which holds references to the vehicles
    std::size_t index;    ///shows the next position in the array; from 0 to capacity, 
                          ///however if index==capacity, it won't be possible to add new Vehicles

public:
    Garage(std::size_t size); /// създава гараж с максимално място за паркиране size.
    Garage& operator=(const Garage& rhs); ///Overloading operator = to safely copy objects
    ~Garage();

    void insert(Vehicle& v); ///добавя превозното средство v в гаража (reference)
    void erase(const char* registration); ///премахва колата с регистрационен номер registration от гаража.
    const Vehicle& at(std::size_t pos) const; ///достъп до елемента намиращ се на позиция pos.
    const Vehicle& operator[](std::size_t pos) const; ///достъп до елемента намиращ се на позиция pos.
    bool empty() const; ///Проверява дали гаражът е празен.
    std::size_t size() const; ///брой елементи (превозни средства) в гаража.
    void clear(); ///изчиства съдържанието на гаража
    const Vehicle* find(const char* registration) const; ///намира и връща превозното средство с регистрационен номер registration в гаража.

};

#endif