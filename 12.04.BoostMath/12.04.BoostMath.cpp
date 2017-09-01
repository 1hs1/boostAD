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

	if (boost::math::signbit(value)) {	// ��������?

		std::cout << "it's negative" << std::endl;

		// ��ȣ ���� ( -�� +�� ���� ). ������ NaN�� ��ȣ�� ���� ����.
		// * -1 ���� ����
		value = boost::math::changesign(value);
		std::cout << "changed to positive -> " << value << std::endl;
	}
} // check_float_inputs

int main()
{
	check_float_inputs(0.0);	// double ��
	check_float_inputs(-110.1f);	// float ��
	check_float_inputs(-11.1l);	// double ��

	check_float_inputs((std::numeric_limits<double>::max)() * 2.0);

	check_float_inputs(std::sqrt(-1.0));

    return 0;
}
