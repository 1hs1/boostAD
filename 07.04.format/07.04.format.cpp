// 07.04.format.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>

#include <boost/format.hpp>
#include <iostream>

class i_hold_some_internals {
	int i;
	std::string s;
	char c;
	// ...
public:
	i_hold_some_internals()
		: i(8)
		, s("Error")
		, c('!')
	{}

	// fmt 파라미터에는 아래 사항이 포함되야 한다.
	//  정수 'i' 를 출력하기 위한 $1$
	//  문자열 's'를 출력하기 위한 $2$ 
	//  문자 'c'를 출력하기 위한 $3$ 
	std::string to_string(const std::string& format_specifier) const {
		boost::format f(format_specifier);
		unsigned char flags = boost::io::all_error_bits;
		flags ^= boost::io::too_few_args_bit;
		f.exceptions(flags);
		return (f % s % i % c).str();
	}
};

int main() {
	i_hold_some_internals class_instance;

	std::cout << class_instance.to_string(
		"%1% Bitwise opreration. "
		"%2%bit %3%\n"
	);

	std::cout << class_instance.to_string(
		"too_few_args_bit %1% %2% %3% %4% \n"
	);

	std::cout << class_instance.to_string(
		"too_many_args_bit %1% \n"
	);

	try {
		class_instance.to_string("%1% %2% %3% %4% %5%\n");
		//assert(false);
	}
	catch (const std::exception& e) {
		// boost::io::too_few_args 예외는 잡아야 한다
		std::cout << e.what() << '\n';
	}

	std::cout << boost::format("%1% %2% %3% %2% %1% \n") % "11" % "22" % "333"; // 'simple' style.

	std::cout << boost::format("(x,y) = (%1%,%2%) \n") % -23 % 35;     // Posix-Printf style
	std::cout << boost::format("(x,y) = (%1$5d,%2$+05d) \n") % -23 % 35;     // Posix-Printf style


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

