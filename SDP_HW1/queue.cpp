#include "queue.h"

myQueue::myQueue()
{

}

void myQueue::init(size_t numOfWorkers)
{
    arrSize = numOfWorkers + 1;
    arr = new worker[arrSize];
}

myQueue::~myQueue()
{
    delete[] arr;
}

int myQueue::size() const
{
    return (arrSize - h + t) % arrSize;
}

bool myQueue::empty() const
{
    return h == t;
}

worker* myQueue::head() const
{
    if(!empty())
    {
        return &arr[h];
    }
    return nullptr;
}

bool myQueue::full() const
{
    return arrSize == size() + 1; /// One free cell for the tail
}

void myQueue::enqueue(worker w)
{
    if(full())
    {
        throw std::exception();
    }

    arr[t] = w;
    t = (t + 1) % arrSize;
}
    
void myQueue::dequeue()
{
    if(empty())
    {
        throw std::exception();
    }

    h = (h + 1) % arrSize;
}