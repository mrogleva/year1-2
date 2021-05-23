#ifndef COMMANDER_H
#define COMMANDER_H

#include "Organizer.hpp"

enum Command{
    VEHICLE, PERSON, ACQUIRE, RELEASE, REMOVE, SAVE, SHOW
};

class Commander
{
private:
    std::vector<std::string> memory; 

    Commander(); 

public:
    Commander(const Commander& other) = delete;
    void operator=(const Commander& other) = delete;
    static Commander& getInstance();

    std::string splitWords(std::string input);
    Command recognizeCommand(std::string input);

    //should save to the vector, as well:
    void execute(Command com, std::string arg1, std::string arg2);
    void execute(Command com, std::string arg1);

    void read(std::string file); //reads commands from a file
    void save(std::string file); //saves the vector to a file
};


#endif