#include <iostream>
#include "ActionHandler.h"

void ConsoleActionHandler::onWorkerSend(int minute, ResourceType resource)
{
    if(resource == ResourceType::banana)
    {
        std::cout<<"W "<<minute<<" banana"<<std::endl;
    }
    else{
        std::cout<<"W "<<minute<<" schweppes"<<std::endl;
    }
}

void ConsoleActionHandler::onWorkerBack(int minute, ResourceType resource)
{
    if(resource == ResourceType::banana)
    {
        std::cout<<"D "<<minute<<" banana"<<std::endl;
    }
    else{
        std::cout<<"D "<<minute<<" schweppes"<<std::endl;
    }
}

void ConsoleActionHandler::onClientDepart(int index, int minute, int banana, int schweppes)
{
    std::cout<<index<<" "<<minute<<" "<<banana<<" "<<schweppes<<std::endl;
}