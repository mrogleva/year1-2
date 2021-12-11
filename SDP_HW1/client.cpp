#include "client.h"

MrazMag_client::MrazMag_client(int arriveMinute, int banana, int schweppes, int maxWaitTime)
{
    this->arriveMinute = arriveMinute;
    this->banana = banana;
    this->schweppes = schweppes;
    this->maxWaitTime = maxWaitTime;

    leaveTime = arriveMinute + maxWaitTime;
}

MrazMag_client::MrazMag_client(Client client) 
    : MrazMag_client(client.arriveMinute, client.banana, client.schweppes, client.maxWaitTime)
{
    
}