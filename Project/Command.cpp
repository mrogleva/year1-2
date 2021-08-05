#include "Command.hpp"

Command::Command(std::string fullCommand)
{
    std::size_t endPos;
    std::size_t startPos;
    std::string temp;

    //get command
    endPos = fullCommand.find(' ');
    command = fullCommand.substr(0, endPos);

    //get parameters
    while (endPos < fullCommand.length())
    {
        while (fullCommand[endPos + 1] == ' ')
        {
            endPos++;
        }

        startPos = endPos + 1;

        if (fullCommand[startPos] == '"')
        {
            startPos += 1;
            endPos = fullCommand.find('"', startPos);

            temp = fullCommand.substr(startPos, endPos - startPos);

            endPos++;
        }
        else
        {
            endPos = fullCommand.find(' ', startPos);

            temp = fullCommand.substr(startPos, endPos - startPos);
        }

        params.push_back(temp);
    }
}

std::string Command::getCommand()
{
    std::string temp;
    temp += command;
    temp += " ";
    for(std::size_t i = 0; i<params.size(); ++i)
    {
        temp += params[i];
        temp += " ";
    }
    temp.pop_back();
    return temp;
}