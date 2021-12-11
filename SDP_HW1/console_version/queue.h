#pragma once

#include <iostream>
#include "worker.h"
 
///realisation of a queue, which will be used to represent our storage

class myQueue
{
    worker* arr = nullptr;
    size_t arrSize = 0;
    int h = 0;
    int t = 0; ///< Marks the next free position 

public:

    myQueue();
    /// We won't need any copies of the queue
    myQueue(const myQueue&) = delete;
	myQueue& operator =(const myQueue&) = delete;
    ~myQueue();
    /// Creates the dynammyc array, which contains our queue 
    void init(size_t numOfWorkers);

    /// How many workers are currently in the queue(storage)
    int size() const;
    bool empty() const;
    bool full() const;
    /// Returns a pointer to the first worker on the queue; nullptr if the queue is empty
    worker* head() const;

    /// Used when a worker arrives at the storage
    void enqueue(worker w);
    /// Used when a worker leaves the storage
    void dequeue();
};