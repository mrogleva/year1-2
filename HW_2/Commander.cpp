#include "Commander.hpp"

Commander::Commander()
{
}

Commander& Commander::getInstance() 
{
    static Commander instance;
    return instance;
}

std::string Commander::splitWords(std::string input)
{
    bool hadLetters = false;
    bool openedQuotes = false;
    std::size_t from = 0;
    std::size_t cnt = 0;
    std::string word;
    for(std::size_t i = 0; i<input.size(); ++i) //kavichkite
    {
        if(openedQuotes)
        {
            if(input[i] == '\"')
            {
                openedQuotes = false;
                word = input.substr(from, cnt);
                return word;
            }
            else
            {
                ++cnt;
                std::cout<<cnt<<"\n";
            }
        }
        if(!openedQuotes && input[i] == '\"')
        {
            openedQuotes = true;
            ++from;
        }
        if(!openedQuotes && input[i] != '\"')
        {
            if((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
            {
                hadLetters = true;
            }
            if(!hadLetters)
            {
                from += 1;
            }
            if(hadLetters && input[i] != ' ')   
            {
                ++cnt;
            }
            if(hadLetters && input[i] == ' ') 
            {
                word = input.substr(from, cnt);
                return word;
            }
        }
        if(i+1 == input.size())
        {
            word = input.substr(from, cnt);
            return word;
        }
    }
}