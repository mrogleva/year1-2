#pragma once

#include <vector>
#include "interface.h"

struct MrazMag_client : Client{
    static int indexGen;

    int index; ///< automatically generated
    int leaveTime;
    bool readyToGo = false; ///< if the purchase is fulfilled and or it is time to leave

    MrazMag_client(int arriveMinute, int banana, int schweppes, int maxWaitTime);
    MrazMag_client(Client client);
};
