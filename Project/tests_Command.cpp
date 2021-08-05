#include "catch2.hpp"
#include "Command.hpp"

TEST_CASE( "recognition", "[Command]" )
{

    SECTION("test")
    {
        Command test("command 123 123 12");
        REQUIRE(test.getCommand() == "command 123 123 12");

    }
}