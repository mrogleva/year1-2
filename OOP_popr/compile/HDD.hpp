#ifndef HDD_H
#define HDD_H

#include "component.hpp"

class HDD : public component
{
public:
	HDD(std::string name, int tb, int readingSpeed, int writingSpeed, double tbPrice, double readingPrice, double writingPrice);
};

#endif