// 02.04.lexical_user_defined.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>
#include <assert.h>
#include <conio.h>

class negative_number {
	unsigned short number_;

public:
	explicit negative_number(unsigned short number = 0)
		: number_(number)
	{}

	unsigned short value_without_sign() const {
		return number_;
	}
};

std::ostream& operator<<(std::ostream& os, const negative_number& num) {
	os << '-' << num.value_without_sign();
	return os;
}

std::istream& operator >> (std::istream& is, negative_number& num) {
	char ch;
	is >> ch;
	if (ch != '-') {
		throw std::logic_error("negative_number class designed to store ONLY negative values");
	}

	unsigned short s;
	is >> s;
	num = negative_number(s);
	return is;
}

void foo1() {
	negative_number n = boost::lexical_cast<negative_number>("-100");
	std::cout << "n : " << n << " value_without_sign : " << n.value_without_sign() << std::endl;

	unsigned int i = boost::lexical_cast<unsigned int>(n);
	std::cout << "i : " << i << " n : " << n << std::endl;

	typedef boost::array<char, 10> arr_t;
	arr_t arr = boost::lexical_cast<arr_t>(n);
	std::cout << "arr[0] : " << arr[0]
		<< " arr[1] : " << arr[1]
		<< " arr[2] : " << arr[2]
		<< " arr[3] : " << arr[3]
		<< " arr[4] : " << arr[4]	//assert(arr[4] == '\0');
		<< std::endl;
}

template <class CharT>
std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const negative_number& num) {
	os << static_cast<CharT>('-') << num.value_without_sign();
	return os;
}

template <class CharT>
std::basic_istream<CharT>& operator >> (std::basic_istream<CharT>& is, negative_number& num) {
	CharT ch;
	is >> ch;
	if (ch != static_cast<CharT>('-')) {
		throw std::logic_error("negative_number class designed to store ONLY negative values");
	}

	unsigned short s;
	is >> s;
	num = negative_number(s);
	return is;
}

void foo2() {
	negative_number n = boost::lexical_cast<negative_number>(L"-1");
	assert(n.value_without_sign() == 1);

	typedef boost::array<wchar_t, 10> warr_t;
	warr_t arr = boost::lexical_cast<warr_t>(n);
	assert(arr[0] == L'-');
	assert(arr[1] == L'1');
	assert(arr[2] == L'\0');
}

int main()
{
	foo1();
	foo2();

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

