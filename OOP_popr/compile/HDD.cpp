#include "HDD.hpp"

HDD::HDD(std::string name, int tb, int readingSpeed, int writingSpeed, double tbPrice, double readingPrice, double writingPrice)
	: component(name)
{
	property temp("tb", tb, tbPrice);
	properties.push_back(temp);

	temp = property("\"reading speed\"", readingSpeed, readingPrice);
	properties.push_back(temp);

	temp = property("\"writing speed\"", writingSpeed, writingPrice);
	properties.push_back(temp);
}