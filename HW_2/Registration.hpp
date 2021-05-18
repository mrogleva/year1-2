#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "Verify.hpp"
#include <string>

class Registration
{
private:
    std::string registration;

public:
    Registration(std::string reg);
    std::string getReg();
  
};



#endif