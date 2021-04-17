#include "catch2.hpp"
#include "Garage.hpp"

TEST_CASE( "Creation and adding veh", "[Garage]" )
{
    const char reg[] = {"reg"};
    Vehicle five1(reg, "des", 5);
    Vehicle five2("123", "123", 5);
    Vehicle one1(reg, "des", 1);
    Vehicle one2("123", "123", 1);
    Garage gar(8);

    SECTION("creation state tests")
    {
        REQUIRE(gar.size() == 0);
        REQUIRE(gar.empty() == true);
        REQUIRE(gar.find(five1.registration()) == nullptr);
    }
    SECTION("add veh 5")
    {
        gar.insert(five1);
        REQUIRE(gar.size() == 1);
        REQUIRE(gar.empty() == false);
        REQUIRE(gar.find(five1.registration()) == &gar.at(0));
        REQUIRE(gar.find(five1.registration()) == &gar[0]);

        SECTION("veh state")
        {
            REQUIRE(&gar.at(0) == &five1);
        }
        SECTION("add another 5")
        {
            REQUIRE_THROWS_AS(gar.insert(five1), std::runtime_error);
            REQUIRE(gar.size() == 1);
            REQUIRE(gar.empty() == false);
        }
        SECTION("add 1 same reg")
        {
            REQUIRE_THROWS_AS(gar.insert(one1), std::runtime_error);
            REQUIRE(gar.size() == 1);
            REQUIRE(gar.empty() == false);
        }
        SECTION("add 1 diff reg")
        {
            gar.insert(one2);
            REQUIRE(gar.size() == 2);
            REQUIRE(gar.empty() == false);
            REQUIRE(gar.find(five1.registration()) == &gar.at(0));
            REQUIRE(gar.find(one2.registration()) == &gar.at(1));
            
            SECTION("one more try")
            {
                REQUIRE(gar.size() == 2);
                REQUIRE_THROWS_AS(gar.insert(one1), std::runtime_error);
            }
        }
    }
}

TEST_CASE( "Removing vehicles and clearing", "[Garage]" )
{
    Garage gar(8);
    char one = '1';
    char two = '2';
    char three = '3';
    Vehicle one1(&one, "des", 1);
    Vehicle one2(&two, "123", 1);
    Vehicle one3(&three, "123", 1);
    gar.insert(one1);
    gar.insert(one2);
    gar.insert(one3);
    
    SECTION("removing")
    {
        gar.erase(&one);
        REQUIRE(gar.size() == 2);
        REQUIRE(gar.empty() == false);
        REQUIRE(gar.find(&three) == &gar.at(0));
        REQUIRE(gar.find(&two) == &gar.at(1));
    }
    SECTION("clearing")
    {
        gar.clear();
        REQUIRE(gar.size() == 0);
        REQUIRE(gar.empty() == true);
        REQUIRE(gar.find(one1.registration()) == nullptr);
        
        SECTION("veh state")
        {
            REQUIRE(one1.space() == 1);
        }
    }
}