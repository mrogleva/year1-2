#pragma once

#include <vector>
#include "interface.h"

/// Represents a client in MrazMag.
/// Named it like that, because it looks cool
struct MrazMag_client : Client{
    int index; ///< added by the store
    int leaveTime; ///< added by the store
    bool readyToGo = false; ///< if the purchase is fulfilled and or it is time to leave

    int bananaTaken = 0;
    int schweppesTaken = 0;

    MrazMag_client(int arriveMinute, int banana, int schweppes, int maxWaitTime);
    MrazMag_client(Client client);
};
