#include "catch2.hpp"
#include "Garage.hpp"

TEST_CASE( "insert Vehicle", "[Garage]" )
{
    const char registration[] = {"reg"};
    const char registration2[] = {"else"};
    const char description[] = {"descript"};
    std::size_t five = 5;
    std::size_t one = 1;

    Vehicle test1(registration, description, five);
    Vehicle test2(registration, description, one);
    Vehicle testOther(registration2, description, five);
    Vehicle testOther2(registration2, description, one);

    Garage Gar(8);

    SECTION("add veh")
    {
        // try
        // {
        //     Gar.insert(test1);
        // }
        // catch(const runtime_error& error)
        // {

        // }
        

    }

}