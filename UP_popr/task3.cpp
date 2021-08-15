#include <iostream>

unsigned** createContainer(std::size_t size);
unsigned* findLongestSequence(unsigned** dominoContainer, std::size_t size, std::size_t& sequenceSize);
void search(unsigned searchFor, unsigned** dominoContainer, std::size_t contSize, bool* available,  
            std::size_t& maxLength, std::size_t currentLength,  unsigned* currentSeq, unsigned* longestSeq);

int main()
{
    std::cout<<"How many tiles would you like to enter?"<<std::endl;
    std::size_t n;
    std::cin>>n;
    if(!std::cin)
    {
        std::cout<<"Please enter a positive number.";
        return 1;
    }
    unsigned** container = createContainer(n);
    if(!container)
    {
        return 1;
    }
    std::size_t sequenceSize = 0;
    unsigned* longestSeq = findLongestSequence(container, n, sequenceSize);
    for(int i = 0; i < sequenceSize - 1; ++i) {
        std::cout<<longestSeq[i]<<" "<<longestSeq[i + 1]<<"  ";
    }
    std::cout<<std::endl;

    delete[] container[0];
    delete[] container;

    return 0;
}

unsigned** createContainer(std::size_t size)
{
    unsigned** container = new(std::nothrow) unsigned*[size];
    if(!container)
    {
        std::cout<<"Memory error.";
        return nullptr;
    }
    container[0] = new(std::nothrow) unsigned[size*2];
    if(!container[0]) 
    {
        delete[] container;
        std::cout<<"Memory error.";
        return nullptr;
    }
    for(size_t i = 1; i < size; ++i)
    {
        container[i] = container[i-1] + 2;
    }
        
    std::cout<<"Please input the domino tile numbers:"<<std::endl;
    for(std::size_t i = 0; i < size; ++i) 
    {
    std::cin>>container[i][0];
    if(!std::cin)
    {
        delete[] container[0];
        delete[] container;
        std::cout<<"Please enter positive numbers.";
        return nullptr;
    }
    std::cin>>container[i][1];
    if(!std::cin)
    {
        delete[] container[0];
        delete[] container;
        std::cout<<"Please enter positive numbers.";
        return nullptr;
    }
    }
    return container;
}

unsigned* findLongestSequence(unsigned** dominoContainer, std::size_t size, std::size_t& sequenceSize)
{
    unsigned* currentSeq = new(std::nothrow) unsigned[size + 1];
    // keeps the values once
    if(!currentSeq)
    {
        std::cout<<"Memory error.";
        return nullptr;
    }

    unsigned* longestSeq = new(std::nothrow) unsigned[size + 1]; 
    if(!longestSeq)
    {
        std::cout<<"Memory error.";
        delete[] currentSeq;    
        return nullptr;
    }
    if(!longestSeq) 
    {
        delete[] longestSeq;
        delete[] currentSeq;   
        std::cout<<"Memory error.";
        return nullptr;
    }

    //flags if the domino on this index is already used
    bool* available = new(std::nothrow) bool[size]; 
    if(!available)
    {
        std::cout<<"Memory error.";
        return nullptr;
    }
    for(std::size_t i = 0; i < size; ++i)
    {
        available[i] = true;
    }
    std::size_t maxLength = 0, currentLength = 1;

    for(std::size_t i = 0; i < size; ++i)
    {
        available[i] = false;
        currentSeq[0] = dominoContainer[i][1];
        search(dominoContainer[i][0], dominoContainer, size, available, maxLength, currentLength, currentSeq, longestSeq);
        currentSeq[0] = dominoContainer[i][0];
        search(dominoContainer[i][1], dominoContainer, size, available, maxLength, currentLength, currentSeq, longestSeq);
        available[i] = true;
    }

    delete[] currentSeq;  
    delete[] available;  
    sequenceSize = maxLength;
    return longestSeq;
}

void search(unsigned searchFor, unsigned** dominoContainer, std::size_t contSize, bool* available,  
            std::size_t& maxLength, std::size_t currentLength,  unsigned* currentSeq, unsigned* longestSeq) 
{
    longestSeq[currentLength] = searchFor;
    ++currentLength;

    if(currentLength > maxLength) 
    { 
        maxLength = currentLength;
        for (unsigned int i = 0; i < maxLength + 1; ++i) {
            longestSeq[i] = currentSeq[i];
        }
    }
    for(std::size_t i = 0; i < contSize; ++i) 
    {  
        if(available[i] && 
            (dominoContainer[i][0] == searchFor || dominoContainer[i][1] == searchFor)) 
        {
            available[i] = false;
            if(dominoContainer[i][0] == searchFor) {
                search(dominoContainer[i][1], dominoContainer, contSize, available, maxLength, currentLength, currentSeq, longestSeq);
            }
            if(dominoContainer[i][1] == searchFor) {
                search(dominoContainer[i][0], dominoContainer, contSize, available, maxLength, currentLength, currentSeq, longestSeq);
            }
            available[i] = true;
        }
    }
    --currentLength;
}
