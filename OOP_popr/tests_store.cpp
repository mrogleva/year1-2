#include "catch2.hpp"
#include "store.hpp"

TEST_CASE( "All tests", "[componentList]" )
{
    store list;
    component test("test");
    test.addProperty("CPU", 2, 1.2);
    list.add(&test);
    SECTION("creation")
    {
        REQUIRE(list.getComponent(0) == &test);
    }
}