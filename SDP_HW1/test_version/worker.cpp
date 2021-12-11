#include "worker.h"

const int RESTOCK_TIME = 60;

worker::worker(ResourceType sentFor, int minuteSent) :
sentFor(sentFor), minuteSent(minuteSent) 
{
    minuteReturn = minuteSent + RESTOCK_TIME;
}

worker::worker()
{
    
}