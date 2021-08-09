#ifndef CPU_H
#define CPU_H

#include "component.hpp"

class CPU : public component
{
public:
	CPU(std::string name, int cores, int frequency, double corePrice, double frequencyPrice);
};

#endif