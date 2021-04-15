#define CATCH_CONFIG_MAIN
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

    SECTION("test full")
    {
        testObj.push_back('d');
        REQUIRE(testObj.size() == 11);
        REQUIRE(testObj.back() == 'd');
        REQUIRE(testObj.at(0) == 'H');
        REQUIRE(testObj.at(2) == 'l');
    }
    SECTION("test empty")
    {
        emptyObj.push_back('z');
        REQUIRE(emptyObj.size() == 1);
        REQUIRE(emptyObj.back() == 'z');
    }
}

TEST_CASE( "removes the last character of the string", "[MyString]" ) //
{
    char test[] = {"Hello1234"};
    MyString testObj(test);

    SECTION("test")
    {
        testObj.pop_back();
        REQUIRE(testObj.at(9) == '\0');
        REQUIRE(testObj.at(8) == '\0');
        REQUIRE(testObj.back() == '3');
        REQUIRE(testObj.at(2) == 'l');
    }
}

