// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Поправителен изпит
// 
// Име: Мария Роглева
// ФН: 82172
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на изпита: 19.08.2021г.
// Начален час на изпита за вашата група: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

class Set
{
public:
	virtual bool member (int x) = 0;

	virtual ~Set(){}
};

class Range : virtual public Set
{
public:
	const int lower;
	const int upper;

	Range(int a, int b);

	bool member (int x) override;
};

Range::Range(int a, int b) : lower(a), upper(b){}

bool Range::member (int x)
{
	return (x >= lower && x <= upper);
}

class EvenNumbers : virtual public Set
{
public:
	bool member (int x) override;
};

bool EvenNumbers::member (int x)
{
	return (x % 2 == 0);
}

class Collection : virtual public Set
{
private:
	int* numbersArray = nullptr;
	std::size_t size = 0;

public:
	Collection();
	Collection(const Collection& other); 
	~Collection();
	
	int getElement(std::size_t pos) const;
	std::size_t getSize() const;
	void insert(int element);
	bool member (int x) override;

	Collection operator+(const Collection& other) const; 
	Collection& operator+=(const Collection& other);

	bool operator<(const Collection& other) const;

};

Collection::Collection()
{ //новият стандарт позволява член-данните да се инициализират с =
}

Collection::Collection(const Collection& other)
{
	numbersArray = new int[other.getSize()];
	size = other.getSize(); //нарочно в този ред
	for(std::size_t i = 0; i < size; ++i)
	{
		numbersArray[i] = other.getElement(i);
	}
}

Collection::~Collection()
{
	if(numbersArray)
	{
		delete[] numbersArray;
	}
	size = 0;
}

int Collection::getElement(std::size_t pos) const
{
	if(pos < size)
	{
		return numbersArray[pos];
	}
	else
	{
		throw std::out_of_range("");
	}
}

std::size_t Collection::getSize() const
{
	return size;
}

void Collection::insert(int element)
{
	for(std::size_t i = 0; i < size; ++i)
	{
		if(numbersArray[i] == element)
		{
			throw std::runtime_error("This element is already in the collection.");
		}
	}
	int* temp = new int[size+1];
	for(std::size_t i = 0; i < size; ++i)
	{
		temp[i] = numbersArray[i];
	}
	temp[size] = element;
	delete[] numbersArray;
	numbersArray = temp;
	size += 1;
}

bool Collection::member (int x)
{
	for(std::size_t i = 0; i < size; ++i)
	{
		if(numbersArray[i] == x)
		{
			return true;
		}
	}
	return false;
}

Collection Collection::operator+(const Collection& other) const
{
	Collection temp;
	for(std::size_t i = 0; i < size; ++i)
	{
		temp.insert(getElement(i));
	}
	for(std::size_t i = 0; i < other.getSize(); ++i)
	{
		try
		{
			temp.insert(other.getElement(i));
		}
		catch(const std::exception& e)
		{}
	}
	return temp;
}

Collection& Collection::operator+=(const Collection& other)
{
	Collection temp = *this + other;
	for(std::size_t i = size; i < temp.getSize(); ++i)
	{
		insert(temp.getElement(i));
	}
	return *this;
}

bool Collection::operator<(const Collection& other) const
{
	if(size == other.getSize())
	{
		for(std::size_t i = 0; i < size; ++i)
		{
			if(this->numbersArray[i] > other.getElement(i))
			{
				return false;
			}
		}
	}
	else
	{
		return (size < other.getSize());
	}
	return true;
}

class Serializer
{
private:
	std::ofstream file;

public:
	Serializer(std::string filePath);
	// не искам копия на обекти от този тип
	Serializer(const Serializer& other) = delete;
	Serializer& operator=(const Serializer& other) = delete;

	~Serializer();	

	void store(Set* obj) const;
};

Serializer::Serializer(std::string filePath)
{
	file.open(filePath);
	if(!file)
	{
		throw std::runtime_error("Unable to open this file.");
	}
}

Serializer::~Serializer()
{
	if(file)
	{
		file.close();
	}
}

void Serializer::store(Set* obj) const
{
	Range range(1, 2);
	EvenNumbers even;
	Collection collection;

	if(file)
	{
		// if(typeid(obj) == typeid(range))
		// {
		// 	file << "r " << obj->lower << " " << obj->upper << '\n';
		// }
		// if(typeid(obj) == typeid(even))
		// {
		// 	file << "e \n";
		// }
		// if(typeid(obj) == typeid(collection))
		// {
		// 	file << "c " << obj->getSize() << " " ;
		// 	for(std::size_t i = 0; i < obj->getSize(); ++i)
		// 	{
		// 		file << obj->getElement() << ' ';
		// 	}
		// }
	}
	else
	{
		throw std::runtime_error("File error.");
	}
}

class Deserializer
{
public:
	static Set* load(std::ifstream file);

};

Set* Deserializer::load(std::ifstream file) 
{
	char key;
	file >> key;
	if(key == 'r')
	{
		int lower, upper;
		file >> lower >> upper;
		Range* range =  new Range(lower, upper);
		return range;
	}
	if(key == 'e')
	{
		EvenNumbers* even = new EvenNumbers;
		return even;
	}
	if(key == 'c')
	{
		std::size_t size;
		file >> size;
		Collection* col = new Collection;
		int currentElement;
		for(std::size_t i = 0; i < size; ++i)
		{
			while(!file.eof())
			{
				file >> currentElement;
				col->insert(currentElement);
			}
		}
		return col;
	}

	throw std::runtime_error("Unable to load this file.");
}

int main()
{
	std::cout << "Hello world!\n";
	return 0;
}