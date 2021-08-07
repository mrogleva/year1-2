#include <iostream>

unsigned maxFrom(int* array, unsigned from, unsigned to)
{
    unsigned max = from;
    for (unsigned i = from + 1; i < to; ++i) 
    {
        if (array[i] > array[max])
        {
            max = i;
        }
    }
    return max;
}

void lengthSort(int* values, int* tosort, unsigned size)
{
    for(unsigned i = 0; i < size-1; ++i) 
    {
        int m = maxFrom(values, i, size);
        int temp = tosort[i];
        tosort[i] = tosort[m];
        tosort[m] = temp;
    }
}

int main()
{
    int arr[] = {5, 7, 3, 4};
    int order[] = {0, 1, 2, 3};
    lengthSort(arr, order, 4);
    for(std::size_t i = 0; i < 4; ++i)
    {
        std::cout<<order[i]<<std::endl;
    }
    return 0;
}