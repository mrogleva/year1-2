#include "configuration.hpp"

void configuration::add(component *component)
{
    for(std::size_t i = 0; i < components.size(); i++)
	{
		if(typeid(*components[i]) == typeid(*component))
		{
			throw std::runtime_error("A component of this type already exists in this configuration.");
		}
	}
    addComponent(component);
}

double configuration::calculatePrice()
{
    double price = 0;
    for(std::size_t i = 0; i < components.size(); i++)
    {
        price += components[i]->calculatePrice();
    }
    double finalPrice = 1.07 * price;
    return finalPrice;
}