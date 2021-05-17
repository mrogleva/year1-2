#include "Verify.hpp"

bool Verify::isLetter(const char a)
{
    if(a >= 'a' && a<= 'z' || a >= 'A' && a <= 'Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Verify::isCapital(const char a)
{
    if(a >= 'A' && a<='Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Verify::isLowercase(const char a)
{
    if(a >= 'a' && a<='z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Verify::isNumber(const char a)
{
    if(a >= '0' && a<='9')
    {
        return true;
    }
    else
    {
        return false;
    }
}