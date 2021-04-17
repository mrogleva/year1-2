//#include "Garage.hpp"
#include "VehAlloc.hpp"
#include <limits>

const std::size_t MAX = 50;

enum Menu{Add = 1, Remove = 2, Print = 3, Exit = 4};

void addVehicle(VehicleAllocator* allocator, Garage* g);
void removeVehicle(Garage* g);
const void printGarage(Garage* g);
const void print(const char* cstring);

int main()
{
    std::size_t input = 0;
    std::cout<<"Enter the Garage capacity: ";
    while (!(std::cin >> input) || input == 0) //This while loop is taken from StackOverFlow. Thanks to @chris
    {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Please enter a positive number.\n";
    }
    VehicleAllocator allocator; 
    Garage gar(input);
    input = 0;
  
    //Menu option; 
    do
    {
        std::cout<<"Choose an option:\n"
                << "Add Vehicle - 1\n"
                << "Remove Vehicle - 2\n"
                << "Print the Garage - 3\n"
                << "Exit - 4\n";
        while (!(std::cin >> input) || input == 0 || input > 4) //@chris
        {
            std::cin.clear(); 
            std:: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Please, choose from:\n"
                      << "Add Vehicle - 1\n"
                      << "Remove Vehicle - 2\n"
                      << "Print the Garage - 3\n"
                      << "Exit - 4\n";
        }

        switch (input)
        {
        case 1:
            try
            {
                addVehicle(&allocator, &gar);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                return 0;
            }
            break;

        case 2:
            removeVehicle(&gar);
            break;

        case 3:
            printGarage(&gar);
            break;

        default:
            break;
        }

    }while(input != 4);
    
    std::cout<<"Goodbye!";

    return 0;
}

void addVehicle(VehicleAllocator* allocator, Garage* g)
{
    char registration[MAX];
    char description[MAX];
    std::size_t space;

    std::cout << "Please enter the registration:\n";
    std::cin >> registration;
    std::cout << "Please enter a description:\n";
    std::cin >> description;
    std::cout << "Please enter how many parking cells does the vehicle take:\n";
    while (!(std::cin >> space) || space == 0) //@chris
    {
        std::cin.clear();               
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "Please enter a positive number.\n";
    }
    
    Vehicle* temp = allocator->allocate(registration, description, space); 
    g->insert(*temp);
}

void removeVehicle(Garage* g)
{
    char registration[MAX];

    std::cout << "Please enter the registration of the Vehicle:\n";
    std::cin >> registration;
    g->erase(registration);
}

const void printGarage(Garage* g)
{
    for(std::size_t i = 0; i < g->size(); ++i)
    {
        std::cout<<"Vehicle "<<i+1<<":\n";
        std::cout<<"Registration: ";
        print(g->at(i).registration());
        std::cout<<"Description: ";
        print(g->at(i).description());        
        std::cout<<"Space: ";
        std::cout<<g->at(i).space()<<std::endl;
    }
}

const void print(const char* cstring)
{
    std::size_t cnt = 0; 
    while(cstring[cnt] != '\0')
    {
        std::cout<<cstring[cnt];
        cnt+=1;
    }
    std::cout<<std::endl;
}

//Благодаря и на Станимир Петров, че ми помогна :)

//This was my idea for the user input verification. However, I found it annoying that 
//you have to restart the program afrer every wrong input
    // try
    // {
    //     std::cin >> input;
    //     if(std::cin.fail() || input == 0)
    //     {
    //        throw std::invalid_argument("Please enter a positive number.");
    //     }
    //     // garageCap = userInput(msg1);
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    //     return 1;
    // }