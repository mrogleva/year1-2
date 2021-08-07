//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Практически изпит
//
// Име: Марио Петров Лалов
// ФН: 82180
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на изпита: 07.07.2021
// Начален час на изпита: 8:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Property
{
private:
	std::string label;
	int quantity;
	double price;

public:
	Property(std::string in_label, int in_quantity, double in_price);
	std::string getLabel() const;
	int getQuantity() const;
	double getPrice() const;
};

Property::Property(std::string in_label, int in_quantity, double in_price)
{
	label = in_label;
	quantity = in_quantity;
	price = in_price;
}

std::string Property::getLabel() const
{
	return label;
}

int Property::getQuantity() const
{
	return quantity;
}

double Property::getPrice() const
{
	return price;
}

class Component
{
protected:
	std::string name;
	std::vector<Property> properties;

public:
	Component(std::string in_name);
	std::string getName() const;
	int getQuantity(std::string in_label) const;
	double calculatePrice();
	void print();
	//used when comparing with requirements
	bool comparableWith(Component &other);
};

Component::Component(std::string in_name)
{
	name = in_name;
}

std::string Component::getName() const
{
	return name;
}

int Component::getQuantity(std::string in_label) const
{
	for (std::size_t i = 0; i < properties.size(); i++)
	{
		if (properties[i].getLabel() == in_label)
		{
			return properties[i].getQuantity();
		}
	}

	//property does not exist
	throw std::invalid_argument("No such property!");
}

double Component::calculatePrice()
{
	double total = 0;

	for (std::size_t i = 0; i < properties.size(); i++)
	{
		total += properties[i].getQuantity() * properties[i].getPrice();
	}

	return total;
}

void Component::print()
{
	std::cout << "Name:" << name << std::endl;

	for (std::size_t i = 0; i < properties.size(); i++)
	{
		std::cout << "Label:" << properties[i].getLabel() << std::endl;
		std::cout << "Quantity:" << properties[i].getQuantity() << std::endl;
		std::cout << "Price:" << properties[i].getPrice() << std::endl;
	}
}

bool Component::comparableWith(Component &other)
{
	//different components
	if (typeid(*this) != typeid(other))
	{
		return false;
	}

	//property is missing
	if (properties.size() != other.properties.size())
	{
		return false;
	}

	for (std::size_t i = 0; i < properties.size(); i++)
	{
		if (other.properties[i].getQuantity() > properties[i].getQuantity())
		{
			return false;
		}
	}

	return true;
}

class CPU : public Component
{
public:
	CPU(std::string name, int cores, int frequency, double core_price, double frquency_price);
};

CPU::CPU(std::string name, int cores, int frequency, double core_price, double frquency_price)
	: Component(name)
{
	Property current("core", cores, core_price);
	properties.push_back(current);

	current = Property("frequency", frequency, frquency_price);
	properties.push_back(current);
}

class RAM : public Component
{
public:
	RAM(std::string name, int gb, int chip, int color_number, double gb_price, double chip_price, double color_price);
};

RAM::RAM(std::string name, int gb, int chip, int color_number, double gb_price, double chip_price, double color_price)
	: Component(name)
{
	Property current("gb", gb, gb_price);
	properties.push_back(current);

	current = Property("chip", chip, chip_price);
	properties.push_back(current);

	current = Property("colors", color_number, color_price);
	properties.push_back(current);
}

class HDD : public Component
{
public:
	HDD(std::string name, int tb, int reading_speed, int writing_speed, double tb_price, double reading_price, double writing_price);
};

HDD::HDD(std::string name, int tb, int reading_speed, int writing_speed, double tb_price, double reading_price, double writing_price)
	: Component(name)
{
	Property current("tb", tb, tb_price);
	properties.push_back(current);

	current = Property("reading_speed", reading_speed, reading_price);
	properties.push_back(current);

	current = Property("writing_speed", writing_speed, writing_price);
	properties.push_back(current);
}

class Store
{
private:
	std::vector<Component *> components;

public:
	void insertComponent(Component *component);
	void removeComponent(std::size_t index);
	Component *&operator[](std::size_t pos);
	void print();
};

void Store::insertComponent(Component *component)
{
	components.push_back(component);
}

void Store::removeComponent(std::size_t index)
{
	components.erase(components.begin() + index);
}

Component *&Store::operator[](std::size_t pos)
{
	return components[pos];
}

void Store::print()
{
	for (std::size_t i = 0; i < components.size(); i++)
	{
		components[i]->print();
	}
}

class Store_builder
{
private:
	std::ifstream file;

public:
	Store_builder(std::string path);
	Store *buildStore();
};

Store_builder::Store_builder(std::string path)
{
	file.open(path);

	//check if file is opened
	if (!file.is_open())
	{
		throw std::logic_error("File problem occured!");
	}
}

Store *Store_builder::buildStore()
{
	Store *store = new Store;

	std::string cur_line;
	std::string component_type;
	std::vector<std::string> properties;

	do
	{
		cur_line.clear();
		std::getline(file, cur_line);

		std::size_t pos = 0;
		std::size_t end;
		std::string current;

		end = cur_line.find(" ", pos);
		component_type = cur_line.substr(pos, end - pos);
		pos = end;

		while (pos < cur_line.length())
		{
			pos++;
			current.clear();

			end = cur_line.find(" ", pos);
			current = cur_line.substr(pos, end - pos);
			pos = end;

			properties.push_back(current);
		}

		if (component_type == "cpu")
		{
			int cores, frequency;
			double core_price, frequency_price;

			for (std::size_t i = 0; i < properties.size(); i++)
			{
				if (properties[i] == "core")
				{
					i++;
					cores = std::stoi(properties[i]);
					i++;
					core_price = std::stod(properties[i]);
				}
				else if (properties[i] == "frequency")
				{
					i++;
					frequency = std::stoi(properties[i]);
					i++;
					frequency_price = std::stod(properties[i]);
				}
			}

			Component *cur_component = new CPU("cpu", cores, frequency, core_price, frequency_price);
			store->insertComponent(cur_component);
		}
		else if (component_type == "ram")
		{
			int gb, chip, color_number;
			double gb_price, chip_price, color_price;

			for (std::size_t i = 0; i < properties.size(); i++)
			{
				if (properties[i] == "gb")
				{
					i++;
					gb = std::stoi(properties[i]);
					i++;
					gb_price = std::stod(properties[i]);
				}
				else if (properties[i] == "chip")
				{
					i++;
					chip = std::stoi(properties[i]);
					i++;
					chip_price = std::stod(properties[i]);
				}
				else if (properties[i] == "color")
				{
					i++;
					color_number = std::stoi(properties[i]);
					i++;
					color_price = std::stod(properties[i]);
				}
			}

			Component *cur_component = new RAM("ram", gb, chip, color_number, gb_price, chip_price, color_price);
			store->insertComponent(cur_component);
		}
		else if (component_type == "hdd")
		{
			int tb, reading_speed, writing_speed;
			double tb_price, reading_price, writing_price;

			for (std::size_t i = 0; i < properties.size(); i++)
			{
				if (properties[i] == "tb")
				{
					i++;
					tb = std::stoi(properties[i]);
					i++;
					tb_price = std::stod(properties[i]);
				}
				else if (properties[i] == "reading")
				{
					i++;
					reading_speed = std::stoi(properties[i]);
					i++;
					reading_price = std::stod(properties[i]);
				}
				else if (properties[i] == "writing")
				{
					i++;
					writing_speed = std::stoi(properties[i]);
					i++;
					writing_price = std::stod(properties[i]);
				}
			}

			Component *cur_component = new HDD("hdd", tb, reading_speed, writing_speed, tb_price, reading_price, writing_price);
			store->insertComponent(cur_component);
		}

	} while (!cur_line.empty());

	return store;
}

class Configuration
{
private:
	std::vector<Component *> components;

	bool checkIfPresent(Component *component);

public:
	Configuration();
	Component *&operator[](std::size_t pos);
	std::size_t size();
	void insert(Component *component);
	double getPrice();
	bool CompareWithRequirement(Configuration *requirement);
};

Configuration::Configuration() {}

Component *&Configuration::operator[](std::size_t pos)
{
	return components[pos];
}

std::size_t Configuration::size()
{
	return components.size();
}

bool Configuration::checkIfPresent(Component *component)
{
	for (std::size_t i = 0; i < components.size(); i++)
	{
		if (typeid(*components[i]) == typeid(*component))
		{
			return true;
		}
	}

	return false;
}

void Configuration::insert(Component *component)
{
	if (checkIfPresent(component))
	{
		throw std::invalid_argument("Component of such type already exists!");
	}

	components.push_back(component);
}

double Configuration::getPrice()
{
	double total = 0;

	for (std::size_t i = 0; i < components.size(); i++)
	{
		total += components[i]->calculatePrice();
	}

	return (total * (107 / 100));
}

bool Configuration::CompareWithRequirement(Configuration *requirement)
{
	bool isPresent = false;

	for (std::size_t i = 0; i < requirement->size(); i++)
	{
		//get name of component
		std::string cur_name = requirement->operator[](i)->getName();
		isPresent = false;

		//check if component in configuration matches the requirment
		for (std::size_t j = 0; j < size(); j++)
		{
			if (cur_name == operator[](j)->getName())
			{
				if (!operator[](j)->comparableWith(*requirement->operator[](i)))
				{
					return false;
				}

				//item of this type checked
				isPresent = true;
				break;
			}
		}

		if (!isPresent)
		{
			return false;
		}
	}

	return true;
}

int main()
{
	//	Store_builder builder("test.txt");
	//	Store *store = builder.buildStore();
	//	store->print();
	Component *com1 = new CPU("cpu", 2, 5, 6, 7);
	Component *com2 = new RAM("ram", 6, 8, 9, 1, 1, 1);
	Component *com3 = new CPU("cpu", 2, 5, 6, 7);
	Component *com4 = new RAM("ram", 5, 11, 9, 1, 1, 1);

	Configuration config;
	Configuration *require = new Configuration;
	config.insert(com1);
	config.insert(com2);
	require->insert(com3);
	require->insert(com4);

	std::cout << config.CompareWithRequirement(require);

	return 0;
}