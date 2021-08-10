#include "store_builder.hpp"
#include <sstream>

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
        std::string currLine;
        std::getline(file, currLine);
        std::stringstream stream(currLine);
        std::string keyword;
        stream >> keyword;
        if (keyword == "CPU")
        {
            int cores;
            double corePrice;
            double frequency;
            double frequencyPrice;

            stream>>cores>>corePrice>>frequency>>frequencyPrice;
            CPU temp(keyword, cores, frequency, corePrice, frequencyPrice);
            myStore.components.push_back(new CPU(temp));
        }
        else if (keyword == "RAM")
        {
            int gb;
            double gbPrice;
            int chip;
            double chipPrice;
            int colors;
            double colorPrice;

            stream>>gb>>gbPrice>>chip>>chipPrice>>colors>>colorPrice;

            RAM temp(keyword, gb, gbPrice, chip, chipPrice, colors, colorPrice);
            myStore.components.push_back(new RAM(temp));
        }
        else if (keyword == "HDD")
        {
            int tb;
            double tbPrice;
            int readingSpeed;
            double readingPrice;
            int writingSpeed;
            double writingPrice;

            stream>>tb>>tbPrice>>readingSpeed>>readingPrice>>writingSpeed>>writingPrice;

            HDD temp(keyword, tb, tbPrice, readingSpeed, readingPrice, writingSpeed, writingPrice);
            myStore.components.push_back(new HDD(temp));
        }
        else
        {
            throw std::runtime_error("Unrecognised keyword." + keyword);
        }
    }

    file.close();
}