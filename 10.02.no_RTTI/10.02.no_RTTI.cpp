// 10.02.no_RTTI.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>

#include <boost/config.hpp>

//#define BOOST_NO_RTTI
#if !defined(BOOST_NO_RTTI) \
    && !defined(BOOST_NO_CXX11_HDR_TYPEINDEX)

#include <typeindex>
using std::type_index;

template <class T>
type_index type_id() {
	return typeid(T);
}

#else

#include <cstring>

struct type_index {
	const char * name_;

	explicit type_index(const char* name)
		: name_(name)
	{}

	const char * name() { return name_; }
};

inline bool operator == (const type_index& v1, const type_index& v2) {
	return !std::strcmp(v1.name_, v2.name_);
}

inline bool operator != (const type_index& v1, const type_index& v2) {
	// 경고 메시지를 억제하기 위해 '!!'를 둠
	return !!std::strcmp(v1.name_, v2.name_);
}

#include <boost/current_function.hpp>
template <class T>
inline type_index type_id() {
	return type_index(BOOST_CURRENT_FUNCTION);
}

#endif

#include <cassert>
int main() {
	assert(type_id<unsigned int>() == type_id<unsigned>());
	assert(type_id<double>() != type_id<long double>());

	std::cout << type_id<double>().name();

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

