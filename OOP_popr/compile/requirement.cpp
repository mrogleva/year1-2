#include "requirement.hpp"

void requirement::add(component *component)
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