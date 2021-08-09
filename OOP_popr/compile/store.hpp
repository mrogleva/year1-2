#ifndef STORE_H
#define STORE_H

#include "componentList.hpp"

class store : public componentList
{
public:
    void add(component *component);
};

#endif