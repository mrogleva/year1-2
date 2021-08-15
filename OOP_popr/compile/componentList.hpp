//parent za store, req and conf
#ifndef COMPONENT_LIST_H
#define COMPONENT_LIST_H

#include "component.hpp"
#include "RAM.hpp"
#include "CPU.hpp"
#include "HDD.hpp"

class componentList
{
protected:
    std::vector<component *> components;
    void addComponent(component *component);
	void print();
	void removeComponent(std::size_t index);

public:
    ~componentList();
    component* getComponent(std::size_t pos);
    std::size_t componentCount();

    friend class configurator;
};

#endif