#include "Vehicle.hpp"
#include "MyString.hpp"

int main()
{
    std::cout<<"Hello!"<<std::endl;
    
    const char registration[] = {"reg"};
    const char description[] = {"descript"};
    std::size_t space = 5;
    
    std::cout<<"Hi!"<<std::endl;
    MyString d(description);
    std::cout<<"Hi!"<<std::endl;
    MyString r(registration);
    std::cout<<"Hi!"<<std::endl;
    d+=r;
    std::cout<<"+= ok"<<std::endl;
    std::cout<<d.size()<<" "<<r.size()<<std::endl;
    std::cout<<"Hi!!!"<<std::endl;
    //try
    //{
        Vehicle testVehicle(registration, description, space);
    //}
    //catch(const std::exception& e)
    //{
    //    std::cerr << e.what() << "error \n";
    //}
    std::cout<<"ok!"<<std::endl;

    return 0;
}