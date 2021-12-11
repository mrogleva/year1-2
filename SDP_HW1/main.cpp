#include "implementation.h"
#include "ActionHandler.h"

const int MINUTES_IN_A_DAY = 1440;

int main()
{
    ConsoleActionHandler output;
    Store* store = createStore();
    store->setActionHandler(&output);

    int W, C;

    std::cin>>W>>C;
    for(int i = 0; i < C; ++i)
    {
        int arrival, banana, schweppes, maxWaitTime;
        std::cin>>arrival>>banana>>schweppes>>maxWaitTime;
        MrazMag_client client(arrival, banana, schweppes, maxWaitTime);
        store->addClients(&client, 1);
    }

    store->init(W, 0, 0);
    store->advanceTo(MINUTES_IN_A_DAY);

    return 0;
}