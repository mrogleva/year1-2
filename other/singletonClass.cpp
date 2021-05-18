#include <iostream>

class Singleton {
	int var1;
	int var2;

	Singleton(int x, double y) 
						: var1(x), var2(y) {}//we need at least one constructor to create an object

	/*if we want it to work on previous versions we can use:
	Singleton(const Singleton&);
	Singleton& operator =(const Singleon&);
	*/
public:
	Singleton(const Singleton&) = delete; //при всеки опит функцията да бъде извикана ще даде грешка
	Singleton& operator =(const Singleon&) = delete;//availiable in c++ 11
	

	static Singleton& instance()
	{
		static Singleton obj(10, 20);//lives till the end of the program and before the function was called
		int x;
		return obj;
	}
	
	void print()
	{
		std::cout << "abc\n";
	}
};

int main()
{
	Singleton::instance().print();

	Singleton& ref = Singleton.instance();
	ref.print();

	
	//Singleton copy = Singleton::instance();//problem - deleted
	return 0;
}