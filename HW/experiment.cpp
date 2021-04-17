#include "MyString.hpp"

int main()
{
    MyString a("abc"), b("xyz");
    MyString c = a+b;
    std::cout<<c.c_str()<<std::endl;

    return 0;
}