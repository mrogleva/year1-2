#include "worker.h"

worker::worker(ResourceType sentFor, int minuteSent) :
sentFor(sentFor), minuteSent(minuteSent) 
{
    minuteReturn = minuteSent + 60;
}