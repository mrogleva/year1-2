#include "Vehicle.hpp"
#include "MyString.hpp"

int main()
{
    std::cout<<"Hello!"<<std::endl;
    
    const char registration[] = {"reg"};
    const char description[] = {"descript"};
    std::size_t space = 5;
    
    std::cout<<"Hi!"<<std::endl;
    MyString s(description);

    try
    {
        Vehicle testVehicle(registration, description, space);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "error \n";
    }
    

    std::cout<<"ok!"<<std::endl;


    return 0;
}