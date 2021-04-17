#include "Garage.hpp"

int main()
{
    Vehicle veh("abc", "123", 5);
    std::cout<<"veh\n";

    Garage gar(8);
    std::cout<<"gar\n";

    gar.insert(veh);
    std::cout<<"inserted\n"<<"size:"<<gar.size();





    return 0;
}