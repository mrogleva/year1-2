#include "catch2.hpp"
#include "Vehicle.hpp"

TEST_CASE( "test Vehicle", "[Vehicle]" )
{
    const char registration[] = {"reg"};
    const char description[] = {"descript"};
    std::size_t space = 5;

    Vehicle testVehicle(registration, description, space);
    const char* reg = testVehicle.registration();
    const char* descript = testVehicle.description();
    std::size_t s = testVehicle.space();

    SECTION("test registration")
    {
        REQUIRE(reg[0] == 'r');
        REQUIRE(reg[1] == 'e');
        REQUIRE(reg[2] == 'g');
        REQUIRE(reg[3] == '\0');
    }
    SECTION("test description")
    {
        REQUIRE(descript[2] == 's');
        REQUIRE(descript[7] == '\0');
    }
    SECTION("test space")
    {
        REQUIRE(s == 5);
    }
}