#include "catch2.hpp"
#include "component.hpp"

TEST_CASE( "All tests", "[component]" )
{
    component test("My component");

    SECTION("creation")
    {
        REQUIRE(test.getName() == "My component");
    }

    test.addProperty("prop", 4, 2);
    test.addProperty("another prop", 1, 12);

    SECTION("adding properties")
    {
        REQUIRE(test.calculatePrice() == 20);
        REQUIRE(test.getQuantity("prop") == 4);
        REQUIRE_THROWS_AS(test.addProperty("prop", 3, 1), std::runtime_error);
    }

    test.removeProperty("prop");

    SECTION("removing properties")
    {
        REQUIRE(test.calculatePrice() == 12);
        REQUIRE_THROWS_AS(test.getQuantity("prop"), std::runtime_error);
        REQUIRE_THROWS_AS(test.removeProperty("prop"), std::runtime_error);
    }

}