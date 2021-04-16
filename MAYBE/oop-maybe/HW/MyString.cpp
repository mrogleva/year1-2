#include <cstring>
#include "MyString.hpp"

MyString::MyString()
{
    string = nullptr;
    strSize = 0;
}

MyString::MyString(const char* str)
{
    size_t tmpSize = 0; 
    while (str[tmpSize]!='\0')
    {
        tmpSize += 1;
    }
    tmpSize += 1; //for the terminating character

    string = new char[tmpSize]; //if an exception is thrown, no object of type MyString is created

    for(size_t i = 0; i<tmpSize; ++i)
    {
        string[i] = str[i]; //да проверя, че си се слага '\0'
    }
    strSize = tmpSize;
}

MyString::~MyString()
{
    delete[] string;
    string = nullptr;
    strSize = 0;
}

char& MyString::at(std::size_t pos)
{
    if(pos<strSize)
    {
        return string[pos];
    }
    else
    {
        throw std::out_of_range("Unavailable position."); 
    }
}

const char& MyString::at(std::size_t pos) const
{
    //
    if(pos<strSize)
    {
        return string[pos];
    }
    else
    {
        throw std::out_of_range("Unavailable position."); 
    }
}

char& MyString::operator[](std::size_t pos)
{
    return at(pos);
}

const char& MyString::operator[](std::size_t pos) const
{
    return at(pos);
}

char& MyString::front()
{
    return at(0);
}

const char& MyString::front() const
{
    return at(0);
}

char& MyString::back()
{
    std::size_t pos = strSize - 2;
    return at(pos);
}

const char& MyString::back() const
{
    std::size_t pos = strSize - 2;
    return at(pos);
}

bool MyString::empty() const
{
    if(strSize == 0)
    {
        return true;
    }
    else
    {
        if(string[0]=='\0')
        {
            return true;
        }
         else
        {
            return false;
        }
    }
}

std::size_t MyString::size() const
{
    return strSize;
}

void MyString::clear()
{
    // for(std::size_t i=0; i<strSize; ++i)
    // {
    //     string[i]='\0';
    // }
    delete[] string;
    string = nullptr;
    strSize = 0;
}

void MyString::push_back(char c)
{
    char* tempString = nullptr;
    if(empty())
    {
        try
        {
            tempString = new char[2];
        }
        catch (std::bad_alloc& ba)
        {
            std::cout<<"Memory error, \""<<c<<"\" was not added.";
            throw;
        } //in case of bad allocation, the function should end here

        tempString[0] = c;
        tempString[1] = '\0';
    }
    else
    {
        try
        {
            tempString = new char[++strSize];
        }
        catch (std::bad_alloc& ba)
        {
            std::cout<<"Memory error, \""<<c<<"\" was not added.";
            throw;
        } //in case of bad allocation, the function should end here
    
        for(std::size_t i=0; i<strSize-2; ++i)
        {
            tempString[i] = string[i];
        }
        tempString[strSize-2] = c;
        tempString[strSize-1] = '\0';
    }
    
    delete[] string; //I am trying to prevent a memory leak :)
    string = tempString;
}

void MyString::pop_back()
{
    char* tempString = nullptr;
    try
    {
        tempString = new char[strSize-1];
    }
    catch (std::bad_alloc& ba)
    {
        std::cout<<"Memory error.";
        throw;
    } //in case of bad allocation, the function should end here

    string[strSize-2]='\0';
    std::strcpy(tempString, string);
    
    delete[] string; //I am trying to prevent a memory leak :)
    string = tempString;
    strSize-=1;
}

MyString& MyString::operator+=(char c)
{
    push_back(c);
    return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
    char* tempString = nullptr;
    try
    {
        tempString = new char[strSize + rhs.strSize - 1];
    }
    catch (std::bad_alloc& ba)
    {
        std::cout<<"Memory error, nothing was added.";
        throw;
    } //in case of bad allocation, the function should end here

    for(std::size_t i=0; i<strSize-1; ++i) //leaving out the '\0' from this
    {
        tempString[i] = string[i];
    }
    for(std::size_t i=0; i < rhs.strSize; ++i)
    {
        tempString[i+strSize-1] = rhs.string[i]; //би трябвало да се включи '\0' от rhs
    }
    strSize = strSize + rhs.strSize - 1; //едно '\0' по-малко
    string = tempString;
    return *this;
}

MyString MyString::operator+(char c) const
{
    MyString sum; 
    sum += this->string;
    sum += c;
    return sum;

}

MyString MyString::operator+(const MyString& rhs) const
{
    MyString sum; 
    sum += this->string;
    sum += rhs;
    return sum;
}

bool MyString::operator==(const MyString &rhs) const
{
    if(strcmp(this->string, rhs.string)==0)
    {
        return true;
    }
    else
    {
        return false;
    }
    /*
    <0	the first character that does not match has a lower value in ptr1 than in ptr2
    0	the contents of both strings are equal
    >0	the first character that does not match has a greater value in ptr1 than in ptr2
    */
}

bool MyString::operator<(const MyString &rhs) const
{
    if(strcmp(this->string, rhs.string)<0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const char* MyString::c_str() const
{
    if(strSize>0)
    {
        char* tmp = new char[strSize]; //
        strcpy(tmp, string);
        const char* str = tmp; 
        tmp = nullptr;
        return str;
    }
    else
    {
        return nullptr;
    }
}