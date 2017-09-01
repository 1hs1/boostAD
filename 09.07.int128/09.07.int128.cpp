// 09.07.int128.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/config.hpp>

namespace project {

#ifdef BOOST_HAS_INT128
	typedef boost::int128_type int_t;
	typedef boost::uint128_type uint_t;

	inline int_t mul(int_t v1, int_t v2, int_t v3) {
		return v1 * v2 * v3;
	}

#else // BOOST_NO_LONG_LONG

#ifdef BOOST_NO_LONG_LONG
#error "This code requires at least int64_t support"
#else
	struct int_t { boost::long_long_type hi, lo; };
	struct uint_t { boost::ulong_long_type hi, lo; };
#endif

#endif // BOOST_NO_LONG_LONG



	inline int_t mul(int_t v1, int_t v2, int_t v3) {
		// do something...

		return int_t();
	}

} // project 네임스페이스



int main() {
	using namespace project;

	mul(int_t(), int_t(), int_t());

	// c++11
	//long long int, unsigned long long int;

	return 0;
}
