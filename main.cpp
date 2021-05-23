#include "Organizer.hpp"

int main()
{
    Organizer& org = Organizer::getInstance();

    org.addPerson("Ivan", 45);
    org.addPerson("Test Petrov", 12);
    org.addPerson("Dragan", 55);
    org.addPerson("Maria", 20);

    return 0;
}