// 07.04.format.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

	// fmt �Ķ���Ϳ��� �Ʒ� ������ ���ԵǾ� �Ѵ�.
	//  ���� 'i' �� ����ϱ� ���� $1$
	//  ���ڿ� 's'�� ����ϱ� ���� $2$ 
	//  ���� 'c'�� ����ϱ� ���� $3$ 
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
		// boost::io::too_few_args ���ܴ� ��ƾ� �Ѵ�
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

