// 01.08.tuple.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <string>
#include <iostream>
#include <conio.h>
#include <set>
#include <assert.h>

using namespace std;

int main()
{
	std::pair<int, std::string> test_pair(10, "Hi");
	std::cout << "pair<0>:" << test_pair.first << endl;
	std::cout << "pair<1>:" << test_pair.second << endl;
	boost::tuple<int, std::string> test_tuple(10, "Hi");
	std::cout << "tuple<0>:" << boost::get<0>(test_tuple) << endl;
	std::cout << "tuple<1>:" << boost::get<1>(test_tuple) << endl;

	using tytuple = boost::tuple<int, double, int>;
	std::set<tytuple> tuplelist;
	
	// tuple_comparison
	tuplelist.insert(boost::make_tuple(1, 2.1, 4));
	tuplelist.insert(boost::make_tuple(2, 20.2, 5));
	tuplelist.insert(boost::make_tuple(3, 300.3, 6));
	for (auto t : tuplelist) {
		std::cout << boost::get<0>(t) << endl;
		std::cout << boost::get<1>(t) << endl;
		std::cout << boost::get<2>(t) << endl;
	}

	boost::tuple<int, float, double, int> quad(10, 1.0f, 10.0, 1);
	int i;
	float f;
	double d;
	int i2;

	boost::tie(i, f, d, i2) = quad;
	assert(i == 10);
	assert(i2 == 1);

	system("pause");

  return 0;
}

