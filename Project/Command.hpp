#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <vector>

class Command ///
{
private:
    std::string command;
    std::vector<std::string> params;

public:
    Command(std::string fullCommand);
    
    std::string getCommand();

};

#endif