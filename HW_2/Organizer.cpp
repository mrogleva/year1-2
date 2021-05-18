#include "Organizer.hpp"

Organizer::Organizer()
{
}

Organizer& Organizer::getInstance() 
{
    static Organizer instance;
    return instance;
}
