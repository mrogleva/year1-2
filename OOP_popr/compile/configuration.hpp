#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "componentList.hpp"

class configuration : public componentList
{
public:
    void add(component *component);
    double calculatePrice();
};

#endif