#include "Registration.hpp"

Registration::Registration(std::string reg)
{
    if(reg.length() == 7)
        {
            if(Verify::isCapital(reg[0]))
            {
                for(std::size_t i = 1; i < 5; ++i)
                {
                    if(!Verify::isNumber(reg[i]))
                    {
                        throw std::runtime_error("This registration is not valid");
                    }
                }
                for(std::size_t i = 5; i < 7; ++i)
                {
                    if(!Verify::isCapital(reg[i]))
                    {
                        throw std::runtime_error("This registration is not valid");
                    }
                }
                registration = reg;
            }
            else 
            {
                throw std::runtime_error("This registration is not valid");
            }
        }
        if(reg.length() == 8)
        {
            if(Verify::isCapital(reg[0]) && Verify::isCapital(reg[1]))
            {
                for(std::size_t i = 2; i < 6; ++i)
                {
                    if(!Verify::isNumber(reg[i]))
                    {
                        throw std::runtime_error("This registration is not valid");
                    }
                }
                for(std::size_t i = 6; i < 8; ++i)
                {
                    if(!Verify::isCapital(reg[i]))
                    {
                        throw std::runtime_error("This registration is not valid");
                    }
                }
                registration = reg;
            }
            else 
            {
                throw std::runtime_error("This registration is not valid");
            }
        }
        if(reg.length() != 8 && reg.length() != 7)
        {
            throw std::runtime_error("This registration is not valid");
        }
}

std::string Registration::getReg()
{
    return registration;
}