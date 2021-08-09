#include "store_builder.hpp"

store* store_builder::buildStore(std::string path)
{
    std::ifstream file;
    file.open(path);
	if(!file.is_open())
	{
		throw std::runtime_error("Unable to open this file.");
	}
    store myStore;
    while (!file.eof())
    {
        std::string componentType;
        file>>componentType;
        // std::string currentLine;
        // std::getline(file, currentLine);
        if(componentType == "cpu")
        {
            
        }
        if(componentType == "ram")
        {

        }
        if(componentType == "hdd")
        {
            
        }


    }

    file.close();

}