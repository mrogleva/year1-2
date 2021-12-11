#include "interface.h"

struct ConsoleActionHandler : ActionHandler
{
    void onWorkerSend(int minute, ResourceType resource);
    void onWorkerBack(int minute, ResourceType resource);
    void onClientDepart(int index, int minute, int banana, int schweppes);
};
