#include "catch2.hpp"
#include "MyString.hpp"

TEST_CASE( "position check", "[MyString]" )
{
    char test[] = {"Hello1234"};
    MyString testObj(test);

    SECTION("test with valid position")
    {
        REQUIRE(testObj.at(2) == 'l');
    }
    SECTION("test with invalid position")
    {
        REQUIRE_THROWS_AS(testObj.at(-2), std::out_of_range);
        REQUIRE_THROWS_AS(testObj.at(25), std::out_of_range);
    }
}

TEST_CASE( "position check const", "[MyString]" )
{
    char test[] = {"Hello1234"};
    const MyString testObj(test);

    SECTION("test with valid position")
    {
        REQUIRE(testObj.at(2) == 'l');
    }
    SECTION("test with invalid position")
    {
        REQUIRE_THROWS_AS(testObj.at(-2), std::out_of_range);
    }
}

TEST_CASE( "access the first element", "[MyString]" ) //
{
    char test[] = {"Hello1234"};
    MyString testObj(test);

    SECTION("test")
    {
        REQUIRE(testObj.front() == 'H');
    }
}

TEST_CASE( "access the first element for const obj", "[MyString]" ) //
{
    char test[] = {"Hello1234"};
    const MyString testObj(test);

    SECTION("test")
    {
        REQUIRE(testObj.front() == 'H');
    }
}

TEST_CASE( "access the last element", "[MyString]" )
{
    char test[] = {"Hello1234"};
    MyString testObj(test);

    SECTION("test as is")
    {
        REQUIRE(testObj.back() == '4');
    }
}

TEST_CASE( "access the last element for const obj", "[MyString]" ) //
{
    char test[] = {"Hello1234"};
    const MyString testObj(test);

    SECTION("test")
    {
        REQUIRE(testObj.back() == '4');
    }
}

TEST_CASE( "check whether the MyString obj is empty", "[MyString]" ) //
{
    char test[] = {"Hello1234"};
    const MyString testObj(test);
    const MyString emptyObj;

    SECTION("test full")
    {
        REQUIRE(testObj.empty() == false);
    }
    SECTION("test empty")
    {
        REQUIRE(emptyObj.empty() == true);
    }
}

TEST_CASE( "returns the size of the string", "[MyString]" )
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    MyString emptyObj;
    
    SECTION("test full")
    {
        REQUIRE(testObj.size() == 10);
    }
    SECTION("test empty")
    {
        REQUIRE(emptyObj.size() == 0);
    }
}

TEST_CASE( "clears the string", "[MyString]" )
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    char test2[] = {};
    MyString emptyObj(test2);

    SECTION("test full")
    {
        testObj.clear();
        REQUIRE(testObj.empty() == true);
    }
    SECTION("test empty")
    {
        emptyObj.clear();
        REQUIRE(emptyObj.empty() == true);
    }
}

TEST_CASE( "func to add a char at the end of the string", "[MyString]" )
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    MyString emptyObj;
    const char z = 'z';

    SECTION("test full")
    {
        testObj.push_back(z);
        REQUIRE(testObj.size() == 11);
        REQUIRE(testObj.back() == 'z');
        REQUIRE(testObj.at(0) == 'H');
        REQUIRE(testObj.at(2) == 'l');
    }
    SECTION("test empty")
    {
        emptyObj.push_back(z);
        REQUIRE(emptyObj.back() == 'z');
        REQUIRE(emptyObj.size() == 2);
    }
}

TEST_CASE("removes the last character of the string", "[MyString]") //
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    testObj.pop_back();

    SECTION("test")
    {
        REQUIRE_THROWS_AS(testObj.at(9), std::out_of_range);
        REQUIRE(testObj.back() == '3');
        REQUIRE(testObj.at(2) == 'l');
    }
}

TEST_CASE("operator += char", "[MyString]")
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    MyString emptyObj;
    const char z = 'z';

    SECTION("test")
    {      
        testObj += z;
        REQUIRE_THROWS_AS(testObj.at(11), std::out_of_range);
        REQUIRE(testObj.back() == 'z');
        REQUIRE(testObj.at(2) == 'l');
    }
    SECTION("empty")
    {
        emptyObj += z;
        REQUIRE_THROWS_AS(emptyObj.at(2), std::out_of_range);
        REQUIRE(emptyObj.back() == 'z');
        REQUIRE(emptyObj.at(0) == 'z');
    }
}

TEST_CASE("operator += MyString", "[MyString]")
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    char rhs[] = {"56789"};
    MyString rhsO(rhs);
    MyString emptyObj;
    
    SECTION("test")
    {
        testObj += rhsO;
        REQUIRE_THROWS_AS(testObj.at(15), std::out_of_range);
        REQUIRE(testObj.back() == '9');
        REQUIRE(testObj.at(9) == '5');
    }
    SECTION("empty +=")
    {
        emptyObj += rhsO;
        REQUIRE(emptyObj.back() == '9');
        REQUIRE(emptyObj.front() == '5');
        REQUIRE_THROWS_AS(emptyObj.at(6), std::out_of_range);
    }
    SECTION("+= empty")
    {
        rhsO += emptyObj;
        REQUIRE(rhsO.back() == '9');
        REQUIRE(rhsO.front() == '5');
        REQUIRE_THROWS_AS(rhsO.at(6), std::out_of_range);
    }
}

TEST_CASE("operator + MyString", "[MyString]")
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    char rhs[] = {"56789"};
    const MyString rhsO(rhs);
    MyString emptyObj;
    
    MyString sumTest = testObj + rhsO;
    MyString sumEmpty = emptyObj + rhsO;

    SECTION("test")
    {
        REQUIRE_THROWS_AS(sumTest.at(14), std::out_of_range);
        REQUIRE(sumTest.back() == '9');
        REQUIRE(sumTest.at(9) == '5');
    }
    SECTION("empty")
    {
        REQUIRE_THROWS_AS(sumEmpty.at(6), std::out_of_range);
        REQUIRE(sumEmpty.back() == '9');
        REQUIRE(sumEmpty.front() == '5');
    }
}

TEST_CASE("operator + char", "[MyString]")
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    MyString emptyObj;
    const char z = 'z';
    
    SECTION("test")
    {
        MyString sumTest = testObj + z;
        REQUIRE(sumTest.size() == 11);
        REQUIRE(sumTest.back() == 'z');
        REQUIRE(sumTest.at(2) == 'l');
        REQUIRE_THROWS_AS(sumTest.at(11), std::out_of_range);
    }
    SECTION("empty")
    {
        MyString sumEmpty = emptyObj + z;
        REQUIRE(sumEmpty.back() == 'z');
        REQUIRE(sumEmpty.at(0) == 'z');
        REQUIRE_THROWS_AS(sumEmpty.at(2), std::out_of_range);
    }
}

TEST_CASE("operator ==", "[MyString]")
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    const MyString testObj2(test);
    char rhs[] = {"56789"};
    const MyString rhsO(rhs);
    MyString empty1;
    const MyString empty2;

    bool y1 = testObj == testObj2;
    bool y2 = testObj2 == testObj2;
    bool y3 = empty1 == empty2;
    bool n1 = testObj == rhsO;
    bool n2 = testObj == empty2;

    SECTION("true, test")
    {
        REQUIRE(y1 == true);
    }
    SECTION("true, the same")
    {
        REQUIRE(y2 == true);
    }
    SECTION("true, empty")
    {
        REQUIRE(y3 == true);
    }
    SECTION("false, test")
    {
        REQUIRE(n1 == false);
    }
    SECTION("false, empty")
    {
        REQUIRE(n2 == false);
    }
}

TEST_CASE("operator <", "[MyString]")
{
    char test[] = {"1234"};
    MyString testObj(test);
    const MyString testObj2(test);
    char rhs[] = {"5678"};
    const MyString rhsO(rhs);
    MyString empty1;
    const MyString empty2;

    bool y1 = testObj < rhsO;
    bool y2 = empty1 < testObj2;
    bool n1 = testObj < empty2;
    bool n2 = empty1 < empty2;
    bool n3 = testObj2 < testObj2;
    bool n4 = rhsO < testObj;

    SECTION("true, test")
    {
        REQUIRE(y1 == true);
    }
    SECTION("true, empty")
    {
        REQUIRE(y2 == true);
    }
    SECTION("false, empty")
    {
        REQUIRE(n1 == false);
    }
    SECTION("false, the same")
    {
        REQUIRE(n2 == false);
        REQUIRE(n3 == false);

    }
    SECTION("false, test")
    {
        REQUIRE(n4 == false);
    }
}

TEST_CASE("c_str", "[MyString]")
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    MyString emptyObj;
    
    const char* str = testObj.c_str();
    const char* emp = emptyObj.c_str();
    
    SECTION("test")
    {
        REQUIRE(str[8] == '4');
        REQUIRE(str[2] == 'l');
    }
    SECTION("empty")
    {
        REQUIRE(emp == nullptr);
    }
}





