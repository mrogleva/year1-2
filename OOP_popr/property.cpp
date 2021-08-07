#include "property.hpp"

property::property(std::string name, int quantity, double price)
{
	this->name = name;
	this->quantity = quantity;
	this->price = price;
}

double property::getPrice() const
{
	return price;
}

std::string property::getName() const
{
	return name;
}

int property::getQuantity() const
{
	return quantity;
}