// 07.05.string_algo.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <string>

#include <boost/algorithm/string/erase.hpp>
void erasing_examples() {
	namespace ba = boost::algorithm;
	std::string str = "Hello  Dolly,   Hello World! hello!";

	std::cout << "\n erase_all_copy   :" << ba::erase_all_copy(str, " ");
	std::cout << "\n erase_first_copy :" << ba::erase_first_copy(str, "H");
	std::cout << "\n erase_last_copy  :" << ba::erase_last_copy(str, "l");
	std::cout << "\n ierase_all_copy  :" << ba::ierase_all_copy(str, "hello");
	std::cout << "\n ierase_nth_copy  :" << ba::ierase_nth_copy(str, "h", 0);

	std::cout << std::endl;

	ba::erase_head(str, 6);
	std::cout << "\n erase_head  :" << str;
	ba::ierase_all(str, "h");
	std::cout << "\n ierase_all  :" << str;
}

#include <boost/algorithm/string/replace.hpp>
void replacing_examples() {
	namespace ba = boost::algorithm;
	std::string str = "Hello  Dolly,   Hello World!";

	std::cout << "\n replace_all_copy:" << ba::replace_all_copy(str, "Dolly", "Jane");
	std::cout << "\n replace_first_copy:" << ba::replace_first_copy(str, "Hello", "Goodbye");
	std::cout << "\n replace_last_copy:" << ba::replace_last_copy(str, "Hello", "Goodbye");
	std::cout << "\n replace_head_copy:" << ba::replace_head_copy(str, 6, "GoodMorning");

	std::cout << std::endl;

	ba::replace_all(str, "Dolly", "Jane");
	std::cout << "\n replace_all:" << str;
	ba::replace_first(str, "Hello", "Goodbye");
	std::cout << "\n replace_first  :" << str;
	ba::replace_last(str, "Hello", "Goodbye");
	std::cout << "\n replace_last  :" << str;
	ba::replace_head(str, 6, "GoodMorning");
	std::cout << "\n replace_head  :" << str;
}

int main() {
	erasing_examples();
	std::cout << std::endl;
	replacing_examples();

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

} // int main()

