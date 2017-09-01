// 12.04.BoostMath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/math/special_functions.hpp>
#include <cassert>

template <class T>
void check_float_inputs(T value) {
	std::cout << std::endl << "== [CHECK] " << value << std::endl;
	if (boost::math::isinf(value)) {
		std::cout << "it's infinite" << std::endl;
	}
	if (boost::math::isnan(value)) {
		std::cout << "it's NaN" << std::endl;
	}

	if (boost::math::signbit(value)) {	// 음수인지?

		std::cout << "it's negative" << std::endl;

		// 부호 변경 ( -를 +로 변경 ). 심지어 NaN의 부호도 변경 가능.
		// * -1 보다 빠름
		value = boost::math::changesign(value);
		std::cout << "changed to positive -> " << value << std::endl;
	}
} // check_float_inputs

int main()
{
	check_float_inputs(0.0);	// double 형
	check_float_inputs(-110.1f);	// float 형
	check_float_inputs(-11.1l);	// double 형

	check_float_inputs((std::numeric_limits<double>::max)() * 2.0);

	check_float_inputs(std::sqrt(-1.0));

    return 0;
}
