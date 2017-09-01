// 10.07.version.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// 부스트 버전 알아내고 최신 기능 가져오기

#include "stdafx.h"
#include <cstddef>
int to_int(const char* str, std::size_t length);

#include <boost/version.hpp>
#include <boost/lexical_cast.hpp>

#if (BOOST_VERSION >= 105200)

int to_int(const char* str, std::size_t length) {
	return boost::lexical_cast<int>(str, length);
}

#else

int to_int(const char* str, std::size_t length) {
	return boost::lexical_cast<int>(
		std::string(str, length)
		);
}

#endif

#include <cassert>
int main() {
	assert(to_int("10000000", 3) == 100);
}