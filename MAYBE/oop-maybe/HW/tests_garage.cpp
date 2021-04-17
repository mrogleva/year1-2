#include "catch2.hpp"
#include "Garage.hpp"

TEST_CASE( "insert Vehicle", "[Garage]" )
{
    Garage gar(8);
    Vehicle five1("reg", "des", 5);
    Vehicle five2("123", "123", 5);
    Vehicle one1("reg", "des", 1);
    Vehicle one2("123", "123", 1);

    SECTION("add veh")
    {
        gar.insert(five1);
        //REQUIRE();

        

    }

}