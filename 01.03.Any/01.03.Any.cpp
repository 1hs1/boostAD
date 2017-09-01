// 01.03.Any.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/any.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

int main()
{
	std::vector<boost::any> some_values;
	some_values.push_back(10);
	const char* c_str = "Hellow there!";
	some_values.push_back(c_str);
	some_values.push_back(std::string("Wow!"));

	std::string& s = boost::any_cast<std::string&>(some_values.back());
	s += "That is great!";
	std::cout << "Any " << s << std::endl;

	int i = boost::any_cast<int>(some_values.front());
	std::cout << "Any " << i << std::endl;

	const char* c = boost::any_cast<const char*>(some_values[1]);
	std::cout << "Any " << c << std::endl;

	std::string* except = boost::any_cast<std::string>(&some_values.front());
	std::cout << "Any " << except << std::endl;

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

