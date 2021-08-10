#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "configuration.hpp"
#include "requirement.hpp"
#include "store.hpp"

class configurator
{
private:
    std::vector<configuration*> configurations;
    configurator();

public:
    configurator(const configurator&) = delete; //при всеки опит функцията да бъде извикана ще даде грешка
	configurator& operator =(const configurator&) = delete;

    static configurator& getInstance()
	{
		static configurator conf;
		return conf;
	}

    configuration* configure(store* st, requirement& req);
    ~configurator();
};

#endif