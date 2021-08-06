#include <iostream>

char* myStrstr(char* haystack, std::size_t hSize, char* needle)
{
    if(!needle || needle[0] == '\0')
    {
        return haystack;
    }
    std::size_t nSize = 0;
    while(needle[nSize])
    {
        nSize += 1;
    }
    if(nSize > hSize)
    {
        return nullptr;
    }
    
    std::size_t i = 0, j = 0, cnt = 0, move = 0;
    while(i < hSize && j < nSize)
    {
        if(haystack[i] == needle[j])
        {
            i += 1;
            j += 1;
            cnt += 1;
        }
        else
        {
            move += 1; //отместване
            i = move;
            j = 0;
            cnt = 0;
        }
    }
    if(cnt == nSize)
    {
        return &haystack[i-cnt];
    }
    else
    {
        return nullptr;
    }
}

int main()
{
    char h[] = {"abcde"};
    char n[] = {"bcd"};
    char x[] = {"abc"};
    char y[] = {"aaa"};

    char* p = myStrstr(h, 6, y);
    for(std::size_t i = 0; i < 3; ++i)
    {
        if(p)
        {
            std::cout<<p[i];
        }
    }
    return 0;
}