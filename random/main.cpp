#include "FileOperator.hpp"

int main(int argc, char** argv)
{
    if(argc == 2)
    {
        try
        {
            FileOperator file(argv[1]);
            std::string input;
            std::getline(std::cin, input);
            file.saveToFile(input);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return 0;
}