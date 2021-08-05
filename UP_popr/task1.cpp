// fix the memory leak in removeDuplicates

#include <iostream>

const unsigned MAX_INPUT_SIZE = 10;

bool smaller(int numA, int numB);
unsigned count(int n);
void sort(int* array, std::size_t size);
unsigned maxFrom(int array[], unsigned from, unsigned to);
std::size_t removeDuplicates(int* array, std::size_t size); //returns the size of the new array

int main()
{
    std::cout<<"Please enter how many numbers would you like to sort.";
    std::size_t numCnt;
    std::cin>>numCnt;
    int* arr = new(std::nothrow) int[numCnt];
    if(!arr)
    {
        std::cout<<"Memory error.";
        return 1;
    }
    std::cout<<"Please enter the numbers:";
    int number;
    for(unsigned i = 0; i<numCnt; ++i)
    {
        if(std::cin>>number)
        {
            arr[i] = number;
        }
        else
        {
            std::cout<<"Invalid input";
            return 1;
        }
    }

    sort(arr, numCnt);
    std::cout<<"Sorted array:\n";
    for(std::size_t i = 0; i < numCnt; ++i)
    {
        std::cout<<arr[i]<<" ";
    }

    std::size_t nCnt = removeDuplicates(arr, numCnt);
    std::cout<<"\nRemoved "<<numCnt - nCnt<<" duplicates:\n";
    for(std::size_t i = 0; i < nCnt; ++i)
    {
        std::cout<<arr[i]<<" ";
    }


    delete[] arr;
    arr = nullptr;

    return 0;
}

bool smaller(int numA, int numB)
{
    int tempA = numA & 0b01010101010101010101010101010101;
    int tempB = numB & 0b01010101010101010101010101010101;
    if(count(tempA) < count(tempB))
    {
        return true;
    }
    if(count(tempA) == count(tempB))
    {
        int nA = numA & 0b10101010101010101010101010101010;
        int nB = numB & 0b10101010101010101010101010101010;
        if(count(nA) < count(nB))
        {
            return true;
        }
    }

    return false;
}

unsigned count(int n) //counts the number of set bits in a number //взаимствано от stackoverflow
{
    unsigned int cnt = 0;
    while (n) {
        cnt += n & 1;
        n >>= 1;
    }
    return cnt;
}

void sort(int* array, std::size_t size)
{
    for(std::size_t i = 0; i < size-1; ++i) {
        int m = maxFrom(array, i, size);
        int temp = array[i];
        array[i] = array[m];
        array[m] = temp; 
    }
}

// Find the index of the max element in a range
unsigned maxFrom(int array[], unsigned from, unsigned to)
{
    unsigned max = from;
    for (unsigned i = from + 1; i < to; ++i) {
        if (!smaller(array[i], array[max]))
        {
            max = i;
        }
    }
    return max;
}

std::size_t removeDuplicates(int* array, std::size_t size)
{
    std::size_t removed = 0;
    for(std::size_t i = 0; i<size-1-removed; ++i) 
    {
        if(array[i] == array[i+1])
        {
            for(std::size_t j = i+1; j<size-1; ++j) //removes the duplicate and shifts left
            {
                array[j] = array[j+1];
            }
            removed += 1;
        }
    }
    if (removed != 0)
    {
        int* temp = new(std::nothrow) int[size-removed];
        if(!temp)
        {
            std::cout<<"Unable to remove duplicates due to memory error.";
            return size;
        }
        for(std::size_t i = 0; i<size-removed; ++i)
        {
            temp[i] = array[i];
        }
        delete[] array;
        array = temp;
        temp = nullptr;
        return size-removed;
    }
    return size;
}