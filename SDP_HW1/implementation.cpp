#include "implementation.h"

const int RESTOCK_AMOUNT = 100;

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
        temp.index = idGen;
        allClients.push_back(temp);

        idGen += 1;
    }
}

void MrazMag::advanceTo(int minute) 
{
    for(int i = 0; i <= minute; ++i)
    {
        playMinute(i);
    }
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
    /// Are there clients arriving?
    for(size_t i = 0; i < allClients.size(); ++i)
    {
        if(allClients.at(i).arriveMinute == minute)
        {
            arrivals(i);
            waitingList.push_back(allClients[i]);
        }
    }
    // /// Are there workers coming back from the storage?
    size_t backWithBanana = 0, backWithSchweppes = 0;
    while(storage.head() && (storage.head()->minuteReturn == minute))
    {
        if(storage.head()->sentFor == ResourceType::banana)
        {
            storage.dequeue();
            backWithBanana += 1;
            bananaExpected -= RESTOCK_AMOUNT;
            bananaAvailable += RESTOCK_AMOUNT;
        }
        if(storage.head()->minuteReturn == minute)
        {
            if(storage.head()->sentFor == ResourceType::schweppes)
            {
                storage.dequeue();
                backWithSchweppes += 1;
                schweppesExpected -= RESTOCK_AMOUNT;
                schweppesAvailable += RESTOCK_AMOUNT;
            }
        }
    }
    for(size_t i = 0; i < backWithBanana; ++i)
    {
        actionHandler->onWorkerBack(minute, ResourceType::banana);
    }
    for(size_t i = 0; i < backWithSchweppes; ++i)
    {
        actionHandler->onWorkerBack(minute, ResourceType::schweppes);
    }

    /// Are there clients who need to go because their wait time is over before their request is completed?
    for(size_t i = 0; i < waitingList.size(); ++i)
    {
        if(waitingList[i].leaveTime == minute && waitingList[i].readyToGo == false)
        {
            /// We give him what we can from his order
            if(bananaAvailable < waitingList[i].banana)
            {
                waitingList[i].bananaTaken = bananaAvailable;
                bananaAvailable = 0;
            }
            else{
                waitingList[i].bananaTaken = waitingList[i].banana;
                bananaAvailable -= waitingList[i].banana;
            }
            if(schweppesAvailable < waitingList[i].schweppes)
            {
                waitingList[i].schweppesTaken = schweppesAvailable;
                schweppesAvailable = 0;
            }
            else{
                waitingList[i].schweppesTaken = waitingList[i].schweppes;
                schweppesAvailable -= waitingList[i].schweppes;
            }
            waitingList[i].readyToGo = true;
        }
    }
   
    /// Is there any other client whose order can be completed now
    for(size_t i = 0; i < waitingList.size(); ++i)
    {
        if( waitingList[i].readyToGo == false 
            && waitingList[i].banana <= bananaAvailable 
            && waitingList[i].schweppes <= schweppesAvailable)
        {
            bananaAvailable -= waitingList[i].banana;
            waitingList[i].bananaTaken = waitingList[i].banana;
            schweppesAvailable -= waitingList[i].schweppes;
            waitingList[i].schweppesTaken = waitingList[i].schweppes;
            waitingList[i].readyToGo = true;
        }
    }
    
    /// All the clients that are ready to go leave
    for(size_t i = 0; i < waitingList.size(); )
    {
        if(waitingList[i].readyToGo)
        {
            actionHandler->onClientDepart(waitingList[i].index, minute, waitingList[i].bananaTaken, waitingList[i].schweppesTaken);
            waitingList.erase(waitingList.begin() + i);
        }
        else{
            ++i;
        }
    }
}

void MrazMag::arrivals(size_t i)
{
    /// There is availability of the desired goods in the store
    if((allClients.at(i).banana <= bananaAvailable) 
        && (allClients.at(i).schweppes <= schweppesAvailable))
    {
        /// Gives what is needed to the client and marks him ready to leave
        bananaAvailable -= allClients[i].banana;
        allClients[i].bananaTaken = allClients[i].banana;
        schweppesAvailable -= allClients[i].schweppes;
        allClients[i].schweppesTaken = allClients[i].schweppes;
        allClients[i].readyToGo = true;
    }
    else{
        /// To make sure the workers are sent in the right order
        int sentForBanana = 0, sentForSchweppes = 0;
        /// Sends workers when a resource is needed and there are workers available
        while((needsBanana(i) || needsSchweppes(i)) && workersAvailable > 0)
        {
            /// Which resource is "missing more"
            if(allClients[i].schweppes - (schweppesAvailable + schweppesExpected)
            > allClients[i].banana - (bananaAvailable + bananaExpected))
            {
                sentForSchweppes += 1;
                schweppesExpected += RESTOCK_AMOUNT;
            }
            else{
                sentForBanana += 1;
                bananaExpected += RESTOCK_AMOUNT;
            }
            workersAvailable -= 1;
        }
        /// Firstly log the workers, sent for banana
        for(size_t j = 0; j < sentForBanana; ++j)
        {
            worker w(ResourceType::banana, allClients[i].arriveMinute);
            storage.enqueue(w);
            actionHandler->onWorkerSend(allClients[i].arriveMinute, ResourceType::banana);
        }
        for(size_t j = 0; j < sentForSchweppes; ++j)
        {
            worker w(ResourceType::schweppes, allClients[i].arriveMinute);
            storage.enqueue(w);
            actionHandler->onWorkerSend(allClients[i].arriveMinute, ResourceType::schweppes);
        }
    }
}