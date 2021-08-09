//parent za store, req and conf
#ifndef COMPONENT_LIST_H
#define COMPONENT_LIST_H

#include "component.hpp"

class componentList
{
protected:
    std::vector<component *> components;
    void addComponent(component *component);
	void print();

public:
    component* getComponent(std::size_t pos);
    std::size_t componentCount();
	void removeComponent(std::size_t index);
};

#endif