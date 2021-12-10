#include "queue.h"

queue::queue(size_t numOfWorkers)
{
    arrSize = numOfWorkers + 1;
    arr = new worker[arrSize];
}

queue::~queue()
{
    delete[] arr;
}

int queue::size() const
{
    return (arrSize - h + t) % arrSize;
}

bool queue::empty() const
{
    return h == t;
}

worker* queue::head() const
{
    if(!empty())
    {
        return &arr[h];
    }
    return nullptr;
}

bool queue::full() const
{
    return arrSize == size() + 1; /// One free cell for the tail
}

void queue::enqueue(worker w)
{
    if(full())
    {
        throw std::exception();
    }

    arr[t] = w;
    t = (t + 1) % arrSize;
}
    
void queue::dequeue()
{
    if(empty())
    {
        throw std::exception();
    }

    h = (h + 1) % arrSize;
}