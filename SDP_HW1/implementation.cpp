#include "implementation.h"

void MrazMag::setActionHandler(ActionHandler *handler) 
{
    actionHandler = handler;
}

void MrazMag::init(int workerCount, int startBanana, int startSchweppes) 
{
    workersAvailable = workerCount;
    bananasAvailable = startBanana;
    schweppesAvailable = startSchweppes;

    storage.init(workerCount);
}

void MrazMag::addClients(const Client *clients, int count)
{
    for(size_t i = 0; i < count; ++i)
    {
        MrazMag_client temp(clients[i]);
        allClients.push_back(temp);
    }
}

void MrazMag::advanceTo(int minute) 
{
    // actionHandler->onWorkerSend(0, ResourceType::banana);
    // actionHandler->onWorkerBack(0, ResourceType::schweppes);
    // actionHandler->onClientDepart(0, 0, 1, 2);
}

int MrazMag::getBanana() const
{
    return bananasAvailable;
}

int MrazMag::getSchweppes() const
{
    return schweppesAvailable;
}

Store *createStore() {
	return new MrazMag();
}