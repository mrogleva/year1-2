#include "component.hpp"

component::component(std::string name)
{
    this->name = name;
}

std::string component::getName() const
{
    return name;
}

int component::getQuantity(std::string propName) const
{
    for(std::size_t i = 0; i < properties.size(); i++)
	{
		if(properties[i].getName() == propName)
		{
			return properties[i].getQuantity();
		}
	}

	throw std::runtime_error("There is no such property.");
}

double component::calculatePrice()
{
	double price = 0;
	for(std::size_t i = 0; i < properties.size(); i++)
	{
		price +=  properties[i].getPrice() * properties[i].getQuantity();
	}

	return price;
}

void component::print()
{
	std::cout << "Name: " << name << std::endl;

	for(std::size_t i = 0; i < properties.size(); i++)
	{
		std::cout << "Property name: " << properties[i].getName() << std::endl;
		std::cout << "Quantity: " << properties[i].getQuantity() << std::endl;
		std::cout << "Price: " << properties[i].getPrice() << std::endl;
	}
}

void component::addProperty(std::string name, int quantity, double price)
{
	for(std::size_t i = 0; i < properties.size(); ++i)
	{
		if(name == properties[i].getName())
		{
			throw std::runtime_error("A component cannot have two properties with the same name.");
		}
	}
	property temp(name, quantity, price);
	properties.push_back(temp);
}

void component::removeProperty(std::string name)
{
	bool removed = false;
	for(std::size_t i = 0; i < properties.size(); ++i)
	{
		if(name == properties[i].getName())
		{
			properties.erase(properties.begin() + i);
			removed = true;
		}
	}
	if(!removed)
	{
		throw std::runtime_error("There is no property with this name.");
	}
}

bool component::betterOrEqual(const component* other) const
{
	for(std::size_t i = 0; i < properties.size(); ++i)
	{
		for(std::size_t j = 0; j < other->properties.size(); ++j)
		{
			if(properties[i].getName() == other->properties[j].getName())
			{
				if(other->properties[j].getQuantity() > properties[i].getQuantity())
				{
					return false;
				}
				break;
			}
		}
	}
	return true;
}

// component* component::createByString(std::string input)
// {
//     std::string propName;
//     int propCaract;
//     double priceCoef;

//     std::size_t index = 0;
//     std::size_t space;
//     while(index < input.size() && input[index] == ' ')
//     {
//         index += 1;
//     }
//     if(index < input.size() && input[index] == '\"')
//     {
//         std::size_t quotation = input.find('\"');
//         if(quotation == -1)
//         {
//             throw std::runtime_error("Invalid format.");
//         }
//         propName = input.substr(index, quotation - index);
//     }
//     else
//     {
//         while(index < input.size() && input[index] == ' ')
//         {
//             index += 1;
//         }
//         space = input.find(' ');
//         if(space == -1)
//         {
//             throw std::runtime_error("Invalid format.");
//         }

//     }
// }