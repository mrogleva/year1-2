#include "configurator.hpp"

configuration* configurator::configure(store* st, requirement& req)
{
    configuration* conf = new configuration;
    std::vector<std::size_t> partsToAdd;
    for(std::size_t i = 0; i < req.componentCount(); ++i)
    {
        bool foundPart = false;
        for(std::size_t j = 0; j < st->componentCount(); ++j)
        {
            if(typeid(*st->getComponent(j)) == typeid(req.getComponent(i)) &&
                st->getComponent(j)->betterOrEqual(req.getComponent(i)))
            {
                foundPart = true;
                partsToAdd.push_back(j);
                break;
            }
        }
        if(!foundPart)
        {
            throw std::runtime_error("Zimbu cannot offer this configuration, due to limited availability.");
        }
    }
    for(std::size_t i = 0; i < partsToAdd.size(); ++i)
    {
        conf->add(st->getComponent(partsToAdd[i]));
        st->removeComponent(partsToAdd[i]);
    }
    configurations.push_back(conf);
    return conf;
}

configurator::~configurator()
{
    for(std::size_t i = 0; i < configurations.size(); ++i)
    {
        delete configurations[i];
    }
}