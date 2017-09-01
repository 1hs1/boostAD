// 01.07.Array.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/array.hpp>
#include <algorithm>
#include <iostream>
using namespace std;

struct add_1 : public std::unary_function<char, void>
{
	void operator()(char& c) const
	{
		++c;
	}
};

using array4_t = boost::array<char, 4>;
array4_t& vector_advance(array4_t& val)
{
	std::for_each(val.begin(), val.end(), add_1());
	return val;
}

/*
*	// 함수에서 배열 반환
*/
int main()
{
	// declare)
	array4_t val = { 0, 1, 2, 3 };

	array4_t val_res;
	val_res = vector_advance(val);

	assert(val.size() == 4);
	assert(val[0] == 1);

	assert(sizeof(val) == sizeof(char) * array4_t::static_size);

	int i = 0;
	cin >> i;

    return 0;
}

