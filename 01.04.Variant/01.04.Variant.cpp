// 01.04.Variant.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/variant.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

int main()
{
	typedef boost::variant<boost::blank, const char*, int, std::string> my_var_t;
	std::vector<my_var_t> some_values;

    std::cout << typeid(some_values).name();

	some_values.push_back(std::string("Wow!"));
	some_values.push_back(10);
	some_values.push_back("Hello there!");

	std::string& s = boost::get<std::string>(some_values[0]);
	s += "This is great!";
	std::cout << "Variant " << s << std::endl;

	int i = boost::get<int>(some_values[1]);
	std::cout << "Variant " << i << std::endl;

	const char* c = boost::get<const char*>(some_values[2]);
	std::cout << "Variant " << c << std::endl;

	int* except = boost::get<int>(&some_values[1]);
	std::cout << "Variant " << except << std::endl;

	my_var_t var1, var2, var3;
	std::cout << "Variant TypeIndex : " << var1.which() << std::endl;
	var1 = 10;
	var2 = "Hello, dear reader";
	var3 = std::string("Hello, dear reader");
	std::cout << "Variant var1 TypeIndex : " << var1.which() << std::endl;
	std::cout << "Variant var2 TypeIndex : " << var2.which() << std::endl;
	std::cout << "Variant var3 TypeIndex : " << var3.which() << std::endl;

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 27)	// ESC key
			{
				break;
			}
		}
	}

	return 0;
}

