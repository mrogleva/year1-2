#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "configuration.hpp"
#include "requirement.hpp"
#include "store.hpp"

class configurator
{
private:
    std::vector<configuration*> configurations;

public:
    configuration* configure(store& st, requirement& req);
    ~configurator();
};

#endif