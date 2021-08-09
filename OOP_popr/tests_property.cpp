#include "catch2.hpp"
#include "property.hpp"

TEST_CASE( "All tests", "[property]" )
{
    property test("Test prop", 3, 3.14);
    REQUIRE(test.getName() == "Test prop");
    REQUIRE(test.getQuantity() == 3);
    REQUIRE(test.getPrice() == 3.14);
}