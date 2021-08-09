#ifndef RAM_H
#define RAM_H

#include "component.hpp"

class RAM : public component
{
public:
	RAM(std::string name, int gb, int chip, int colors, double gbPrice, double chipPrice, double colorPrice);
};

#endif