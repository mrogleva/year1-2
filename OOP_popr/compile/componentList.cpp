#include "componentList.hpp"

void componentList::addComponent(component *component)
{
	components.push_back(component);
}

void componentList::removeComponent(std::size_t pos)
{
    if(pos < components.size())
    {
        components.erase(components.begin() + pos);
    }
    throw std::out_of_range("");
}

component* componentList::getComponent(std::size_t pos)
{
    if(pos < components.size())
    {
        return components[pos];
    }
	throw std::out_of_range("");
}

void componentList::print()
{
	for (std::size_t i = 0; i < components.size(); i++)
	{
		components[i]->print();
	}
}

std::size_t componentList::componentCount()
{
    return components.size();
}