// 12.03.RealRandom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

const unsigned int R_MIN = 1;
const unsigned int R_MAX = 1000;
const unsigned int R_COUNT = 10;

template <typename GENERATOR, typename RANDOM>
void test(GENERATOR &g, RANDOM &r)
{
	for (unsigned int i = 0; i < R_COUNT; ++i) {
		std::cout << r(g) << '\t';
	}
}



#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
void test_normal() {
	test(boost::random::mt19937(), boost::random::uniform_int_distribution<>(R_MIN, R_MAX));
}


#include <boost/config.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
void test_powerful() {
	static const std::string provider =
#ifdef BOOST_WINDOWS
		"Microsoft Strong Cryptographic Provider"
#else
		"/dev/urandom"
#endif
		;

	test(boost::random_device(provider), boost::random::uniform_int_distribution<>(R_MIN, R_MAX));
}

int main()
{
	
	test_normal();

	std::cout << std::endl << std::endl << std::endl;

	test_powerful();


	//- 랜덤 종류와 성능 지표
	// http://www.boost.org/doc/libs/1_63_0/doc/html/boost_random/performance.html

	//- Boost Random 레퍼런스
	// http://www.boost.org/doc/libs/1_63_0/doc/html/boost_random/reference.html

    return 0;
}

