#include <cstring>
#include "MyString.hpp"

MyString::MyString()
{
    string = new char[1];
    string[0] = '\0';
    strSize = 1;
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

MyString& MyString::operator=(const MyString& rhs)
{
    if(*this == rhs)
    {
        return *this;
    }
    else
    {
        clear();
        *this+=rhs;
    }
}

MyString::~MyString()
{
    delete[] string;
    string = nullptr;
    strSize = 0;
}

char& MyString::at(std::size_t pos)
{
    if(pos<strSize-1)
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
    if(strSize == 0 || strSize ==1)
    {
        return true;
    }
    if(string[0]=='\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::size_t MyString::size() const
{
    return strSize;
}

void MyString::clear()
{
    delete[] string;
    string = new char[1];
    string[0] = '\0';
    strSize = 1;
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
        strSize = 2;
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
    if(empty()==false)
    {
        char* tempString = nullptr;
        try
        {
            tempString = new char[--strSize];
        }
        catch (std::bad_alloc& ba)
        {
            std::cout<<"Memory error, nothing was removed.";
            throw;
        } //in case of bad allocation, the function should end here

        string[strSize-1]='\0';
        std::strcpy(tempString, string);
        
        delete[] string; //I am trying to prevent a memory leak :)
        string = tempString;
    }
}

MyString& MyString::operator+=(char c)
{
    push_back(c);
    return *this;
}

MyString& MyString::operator+=(const MyString& rhs)
{
    if(rhs.empty())
    {
        return *this;
    }

    char* tempString = nullptr;
    if(empty())
    {
        try
        {
            tempString = new char[rhs.size()];
        }
        catch (std::bad_alloc& ba)
        {
            std::cout<<"Memory error, nothing was added.";
            throw;
        } //in case of bad allocation, the function should end here
        strcpy(tempString, rhs.c_str());
        strSize = rhs.size();
        delete[] string;
        string = tempString;
        return *this;
    }
    else 
    {
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
            tempString[i+strSize-1] = rhs.string[i]; //includes '\0' from rhs
        }
        strSize = strSize + rhs.strSize - 1;
        delete[] string;
        string = tempString;
        return *this;
    } 
}

MyString MyString::operator+(char c) const
{
    MyString sum(c_str()); 
    sum += c;
    return sum;
}

MyString MyString::operator+(const MyString& rhs) const
{
    MyString sum(c_str()); 
    sum += rhs;
    return sum;
}

bool MyString::operator==(const MyString &rhs) const
{
    if(empty()==false && rhs.empty()==false)
    {
        if(strcmp(this->string, rhs.string)==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(empty() && rhs.empty())
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
    if(empty()==false && rhs.empty()==false)
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
    if(empty() && rhs.empty())
    {
        return false;
    }
    if(empty()==false && rhs.empty())
    {
        return false;
    }
    if(empty() && rhs.empty()==false)
    {
        return true;
    }
}

const char* MyString::c_str() const
{
    return string;
}