#include <iostream>

#ifndef HW_LIB
#define HW_LIB

class MyString ///For conveniently working with strings
{
private:
    char* string; ///pointer to the beginning of the string
    std::size_t strSize; ///stores the size of the string, incl the terminating character

public:
    MyString(); ///Default constructor. Creates an empty MyString
    MyString(const char* str); ///Makes an object for given string
    MyString& operator=(const MyString& rhs); ///copy

    ~MyString(); 

    char& at(std::size_t pos); ///to access the element at a given position
    const char& at(std::size_t pos) const; ///to access the element at a given position for constants
    

    char& front(); ///to access the first element of the string
    const char& front() const; ///to access the first element of the string, const

    char& back(); ///to access the last element of the string 
    const char& back() const; ///to access the last element of the string, const

    bool empty() const; ///checks if the string is empty
    std::size_t size() const; ///returns the size of the string
    void clear(); ///clears the string 
    
    void push_back(char c); ///adds character c at the end of the string SEG
    void pop_back(); ///removes the last character of the string; assert ..

    char& operator[](std::size_t pos); ///overloads operator []
    const char& operator[](std::size_t pos) const; ///overloads operator [] for const

    MyString& operator+=(char c); ///добавя символа c в края на низа. Операцията да дава strong exception guarantee. Връща *this.
    MyString& operator+=(const MyString& rhs); ///конкатенира съдържанието на str към текущия низ. Операцията да дава strong exception guarantee. Връща *this.
    MyString operator+(char c) const; ///Връща нов символен низ, който се получава от текущия, конкатениран със символа c.
    MyString operator+(const MyString& rhs) const; ///Връща нов символен низ, който се получава от текущия, конкатениран с низа rhs.
    bool operator==(const MyString &rhs) const; ///Проверява дали два символни низа са еднакви.
    bool operator<(const MyString &rhs) const; ///Проверява дали текущият низ предхожда лексикографски rhs.

    const char* c_str() const; ///връща указател към null-terminated масив от тип char, който има съдържание идентично с това на низа.

};


#endif