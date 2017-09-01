// 10.04.constexpr_c++11.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_CONSTEXPR) \
	&& !defined(BOOST_NO_CXX11_HDR_ARRAY)

template <class T>
constexpr int get_size(const T& val) {
	return val.size() * sizeof(typename T::value_type);
}

// boost 버젼
template <class T, T Value>
struct integral_constant {
	BOOST_STATIC_CONSTEXPR T value = Value;	// ?
	//BOOST_CONSTEXPR T value = Value;
	BOOST_CONSTEXPR operator T() const {
		return this->value;
	}
};

char array[integral_constant<int, 10>()];

#else
#error "This code requires C++11 constexpr and std::array"
#endif


#include <array>
#include <cassert>
int main() {

	std::array<short, 5> arr;
	assert(get_size(arr) == 5 * sizeof(short));

	std::cout << "get_size(arr) : " << get_size(arr) << std::endl;
	std::cout << "5 * sizeof(short) : " << 5 * sizeof(short) << std::endl;


	unsigned char data[get_size(arr)];

	assert(sizeof(array) == 10);
	(void)data;

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
}

// http://egloos.zum.com/sweeper/v/3147813

