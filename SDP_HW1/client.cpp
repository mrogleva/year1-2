#include "client.h"

int MrazMag_client::indexGen = 0;

MrazMag_client::MrazMag_client(int arriveMinute, int banana, int schweppes, int maxWaitTime)
{
    this->arriveMinute = arriveMinute;
    this->banana = banana;
    this->schweppes = schweppes;
    this->maxWaitTime = maxWaitTime;

    this->index = indexGen++;
    leaveTime = arriveMinute + maxWaitTime;
}

MrazMag_client::MrazMag_client(Client client) 
    : MrazMag_client(client.arriveMinute, client.banana, client.schweppes, client.maxWaitTime)
{
    
}