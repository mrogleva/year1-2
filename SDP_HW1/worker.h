#pragma once

#include "interface.h"

struct worker
{
    ResourceType sentFor;
    int minuteSent;
    int minuteReturn;
};