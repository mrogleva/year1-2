#include "catch2.hpp"
#include "MyString.hpp"

TEST_CASE( "position check", "[MyString]" )
{
    char test[] = {"Hello1234"};
    //char* str = &test[0];
    //MyString testObj(str);
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
    SECTION("test with the last position")
    {
        REQUIRE(testObj.at(9) == '\0');
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
    SECTION("test with the last position")
    {
        REQUIRE(testObj.at(9) == '\0');
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
    SECTION("test with more than one terminating characters")
    {
        testObj.pop_back();
        REQUIRE(testObj.back() == '3');
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
        REQUIRE(emptyObj.size() == 1);
        REQUIRE(emptyObj.back() == 'z');
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
        REQUIRE(testObj.at(8) == '\0');
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
    testObj += z;
    emptyObj += z;

    SECTION("test")
    {
        REQUIRE_THROWS_AS(testObj.at(11), std::out_of_range);
        REQUIRE(testObj.at(10) == '\0');
        REQUIRE(testObj.back() == 'z');
        REQUIRE(testObj.at(2) == 'l');
    }
    SECTION("empty")
    {
        REQUIRE_THROWS_AS(testObj.at(2), std::out_of_range);
        REQUIRE(testObj.at(1) == '\0');
        REQUIRE(testObj.back() == 'z');
        REQUIRE(testObj.at(0) == 'z');
    }
}

TEST_CASE("operator += string", "[MyString]")
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    const char rhs[] = {"56789"};
    MyString emptyObj;
    testObj+=rhs;
    emptyObj+=rhs;

    SECTION("test")
    {
        REQUIRE_THROWS_AS(testObj.at(14), std::out_of_range);
        REQUIRE(testObj.at(13) == '\0');
        REQUIRE(testObj.back() == '9');
        REQUIRE(testObj.at(9) == '5');
    }
    SECTION("empty")
    {
        REQUIRE_THROWS_AS(testObj.at(6), std::out_of_range);
        REQUIRE(testObj.at(5) == '\0');
        REQUIRE(testObj.back() == '9');
        REQUIRE(testObj.front() == '5');
    }
}

TEST_CASE("operator + char", "[MyString]")
{
    char test[] = {"Hello1234"};
    MyString testObj(test);
    MyString emptyObj;
    const char z = 'z';
    MyString sumTest = testObj + z;
    MyString sumEmpty = emptyObj + z;
    
    SECTION("test")
    {
        REQUIRE_THROWS_AS(sumTest.at(11), std::out_of_range);
        REQUIRE(sumTest.at(10) == '\0');
        REQUIRE(sumTest.back() == 'z');
        REQUIRE(sumTest.at(2) == 'l');
    }
    SECTION("empty")
    {
        REQUIRE_THROWS_AS(sumEmpty.at(2), std::out_of_range);
        REQUIRE(sumEmpty.at(1) == '\0');
        REQUIRE(sumEmpty.back() == 'z');
        REQUIRE(sumEmpty.at(0) == 'z');
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
        REQUIRE(sumTest.at(13) == '\0');
        REQUIRE(sumTest.back() == '9');
        REQUIRE(sumTest.at(9) == '5');
    }
    SECTION("empty")
    {
        REQUIRE_THROWS_AS(sumEmpty.at(6), std::out_of_range);
        REQUIRE(sumEmpty.at(5) == '\0');
        REQUIRE(sumEmpty.back() == '9');
        REQUIRE(sumEmpty.front() == '5');
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
        REQUIRE_THROWS_AS(str[10], std::out_of_range);
        REQUIRE(str[9] == '\0');
        REQUIRE(str[8] == 'z');
        REQUIRE(str[2] == 'l');
    }
    SECTION("empty")
    {
        REQUIRE_THROWS_AS(emp[0], std::out_of_range);
    }
}