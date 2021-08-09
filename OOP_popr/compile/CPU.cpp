#include "CPU.hpp"

CPU::CPU(std::string name, int cores, int frequency, double corePrice, double frequencyPrice)
: component(name)
{
    property temp("core", cores, corePrice);
	properties.push_back(temp);
    temp = property("frequency", frequency, frequencyPrice);
	properties.push_back(temp);
}