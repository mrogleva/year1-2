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
// Ден, в който се явявате на изпита: 16.08.2021г.
// Начален час на изпита за вашата група: 10:30
// Кой компилатор използвате: GCC

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>

struct DateAndTime
{
	unsigned hour;
	unsigned minutes;
	unsigned date;
	unsigned month;
};

class Ticket
{
protected:
	DateAndTime concert;
	unsigned hall;
	double basePrice;
public:
	Ticket(unsigned hour, unsigned minutes, unsigned date, unsigned month, unsigned hall, double basePrice);
	virtual ~Ticket(){}

	virtual double getPrice() = 0;

};

Ticket::Ticket(unsigned hour, unsigned minutes, unsigned date, unsigned month, unsigned hall, double basePrice)
{
	if((hour < 0 || hour > 24) || (minutes < 0 || minutes > 59))
	{
		throw std::logic_error("Invalid input for the time.");
	}
	if((month < 1 || month > 12) || (date < 1 || date > 31)) //////////////////////////////vs mesec
	{
		throw std::logic_error("Invalid input for the date.");
	}
	if(hall < 1 || hall > 10)
	{
		throw std::logic_error("Invalid input for the hall.");
	}
	DateAndTime when;
	when.hour = hour;
	when.minutes = minutes;
	when.date = date;
	when.month = month;
	this->concert = when;
	this->hall = hall;
	this->basePrice = basePrice;
}

class PersonalTicket : virtual public Ticket
{
	std::string name;
	unsigned launge;

public:
	PersonalTicket(unsigned hour, unsigned minutes, unsigned date, unsigned month, unsigned hall, double basePrice, 
	std::string name, unsigned launge);

	double getPrice() override;
};

PersonalTicket::PersonalTicket(unsigned hour, unsigned minutes, unsigned date, unsigned month, unsigned hall, double basePrice, 
	std::string name, unsigned launge) : Ticket(hour, minutes, date, month, hall, basePrice)
	{
		this->name = name;
		this->launge = launge;
	}

double PersonalTicket::getPrice()
{
	return basePrice*3;
}

class SpecialTicket : virtual public PersonalTicket
{
	DateAndTime meeting;

public:
	SpecialTicket(unsigned hour, unsigned minutes, unsigned date, unsigned month, unsigned hall, double basePrice, 
	std::string name, unsigned launge, unsigned hourM, unsigned minutesM, unsigned dateM, unsigned monthM);

	double getPrice() override;

};

SpecialTicket::SpecialTicket(unsigned hour, unsigned minutes, unsigned date, unsigned month, unsigned hall, double basePrice, 
	std::string name, unsigned launge, unsigned hourM, unsigned minutesM, unsigned dateM, unsigned monthM) 
	: PersonalTicket(hour, minutes, date, month, hall, basePrice, name, launge)
	, Ticket(hour, minutes, date, month, hall, basePrice)
{
	if((hourM < 0 || hourM > 24) || (minutesM < 0 || minutesM > 59))
	{
		throw std::logic_error("Invalid input for the time.");
	}
	if((monthM < 1 || monthM > 12) || (dateM < 1 || dateM > 31)) //////////////////////////////vs mesec
	{
		throw std::logic_error("Invalid input for the date.");
	}
	DateAndTime meeting;
	meeting.hour = hourM;
	meeting.minutes = minutesM;
	meeting.date = dateM;
	meeting.month = monthM;
	this->meeting = meeting;
}

double SpecialTicket::getPrice()
{
	return 0;
}

double priceCalculator(Ticket** tickets, std::size_t num) 
//подава се указател към динамичен масив от указатели от тип Ticket. Те всъщност сочат към обект наследник, но по този начин 
// няма нужда да уточняваме кой точно наследник. виртуалнатя ф-я се грижи да се извика правилната getPrice()
{
	double price = 0;
	for(std::size_t i = 0; i < num; ++i)
	{
		price += tickets[i]->getPrice();
	}
	return price;
}


int main()
{
	std::cout << "Hello world!\n";
	try
	{
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}