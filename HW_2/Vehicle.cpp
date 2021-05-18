#include "Vehicle.hpp"

Vehicle::Vehicle(Registration registration, std::string description) : Registration(registration)
{
    this->description = description;
    owner = nullptr;
}