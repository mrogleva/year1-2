#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include "property.hpp"

class component
{
protected:
	std::string name;
	std::vector<property> properties;

public:
	component(std::string name);
	std::string getName() const;
	int getQuantity(std::string propName) const;
	double calculatePrice();
	
	void addProperty(std::string name, int quantity, double price); //proverka da ne se povt imeto
	void removeProperty(std::string name);
    
	bool betterOrEqual(const component* other) const;
	void print();
};

#endif