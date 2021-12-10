#include "implementation.h"

void MrazMag::setActionHandler(ActionHandler *handler) 
{
    actionHandler = handler;
}

void MrazMag::init(int workerCount, int startBanana, int startSchweppes) 
{
    workersAvailable = workerCount;
    bananaAvailable = startBanana;
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
    return bananaAvailable;
}

int MrazMag::getSchweppes() const
{
    return schweppesAvailable;
}

Store *createStore() {
	return new MrazMag();
}

bool MrazMag::needsBanana(size_t index)
{
    return allClients[index].banana > (bananaAvailable + bananaExpected);
}

bool MrazMag::needsSchweppes(size_t index)
{
    return allClients[index].schweppes > (schweppesAvailable + schweppesExpected);
}

void MrazMag::playMinute(int minute)
{
    for(size_t i = 0; i < allClients.size(); ++i)
    {
        if(allClients[i].arriveMinute == minute)
        {
            /// there is availability of the desired goods in the store
            if((allClients[i].banana <= bananaAvailable) 
                && (allClients[i].schweppes <= schweppesAvailable))
            {
                bananaAvailable -= allClients[i].banana;
                schweppesAvailable -= allClients[i].schweppes;
                allClients[i].readyToGo = true;
            }
            else{
                while((needsBanana(i) || needsSchweppes(i)) && workersAvailable > 0)
                {
                    if(allClients[i].schweppes - (schweppesAvailable + schweppesExpected)
                    > allClients[i].banana - (bananaAvailable + bananaExpected))
                    {
                        worker w(ResourceType::schweppes, minute);
                        storage.enqueue(w);
                        schweppesExpected += 100;
                    }
                    else{
                        worker w(ResourceType::banana, minute);
                        storage.enqueue(w);
                        bananaExpected += 100;
                    }
                    workersAvailable -= 1;
                }
            }
            waitingList.push_back(allClients[i]);
        }
    }
}