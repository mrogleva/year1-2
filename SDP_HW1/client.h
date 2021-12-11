#pragma once

#include <vector>
#include "interface.h"

/// Named it like that, because it looks cool
struct MrazMag_client : Client{
    static int indexGen;

    int index; ///< automatically generated
    int leaveTime;
    bool readyToGo = false; ///< if the purchase is fulfilled and or it is time to leave

    int bananaTaken = 0;
    int schweppesTaken = 0;

    MrazMag_client(int arriveMinute, int banana, int schweppes, int maxWaitTime);
    MrazMag_client(Client client);
};
