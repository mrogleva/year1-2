#ifndef STORE_BUILDER_H
#define STORE_BUILDER_H


#include <fstream>
#include "store.hpp"
#include "RAM.hpp"
#include "CPU.hpp"
#include "HDD.hpp"

class store_builder 
{
public:
	static store *buildStore(std::string path);
};

#endif