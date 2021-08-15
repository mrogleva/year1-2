#include "catch2.hpp"
#include "configuration.hpp"

TEST_CASE( "All tests", "[componentList, Configuration]" )
{
    RAM comp1("ram", 2, 1, 5, 12, 1, 4);
    CPU comp2("cpu", 4, 2, 12, 1);
    RAM comp3("ram2", 2, 1, 5, 12, 1, 4);
    configuration conf;
    SECTION("creation")
    {
        REQUIRE(conf.componentCount() == 0);
        REQUIRE(conf.calculatePrice() == 0);
    }
    conf.add(&comp1);
    SECTION("add 1")
    {
        REQUIRE(conf.componentCount() == 1);
        REQUIRE(conf.calculatePrice() == 45);
    }
    conf.add(&comp2);
    SECTION("add 2")
    {
        REQUIRE(conf.componentCount() == 2);
        REQUIRE(conf.calculatePrice() == 95);
    }
    SECTION("add 3")
    {
        REQUIRE_THROWS_AS(conf.add(&comp3), std::runtime_error);
        REQUIRE(conf.componentCount() == 2);
    }
}

