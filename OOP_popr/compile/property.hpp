#ifndef PROPERTY_H
#define PROPERTY_H

#include <iostream>
#include <string>

class property
{
	std::string name;
	int quantity;
	double price;

public:
	property(std::string name, int quantity, double price);
	double getPrice() const;
	std::string getName() const;
	int getQuantity() const;
};

#endif