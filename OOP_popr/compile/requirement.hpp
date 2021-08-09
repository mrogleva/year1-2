#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include "componentList.hpp"

class requirement : public componentList
{
public:
    void add(component *component);
};

#endif