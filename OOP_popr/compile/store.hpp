#ifndef STORE_H
#define STORE_H

#include "componentList.hpp"

class store : public componentList
{
public:
    void add(component *component);

    friend class store_builder;
};

#endif