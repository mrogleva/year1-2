#include "RAM.hpp"

RAM::RAM(std::string name, int gb, int chip, int colors, double gbPrice, double chipPrice, double colorPrice)
	: component(name)
{
	property temp("gb", gb, gbPrice);
	properties.push_back(temp);
	temp = property("chip", chip, chipPrice);
	properties.push_back(temp);
	temp = property("colors", colors, colorPrice);
	properties.push_back(temp);
}