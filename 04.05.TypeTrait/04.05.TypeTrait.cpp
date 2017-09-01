// 04.05.TypeTrait.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <vector>
#include <boost/type_traits/integral_constant.hpp>

template <class T>
struct is_stdvector : boost::false_type {};

template <class T, class Allocator>
struct is_stdvector<std::vector<T, Allocator> > : boost::true_type {};

template<class T>
struct is_array : boost::false_type {};
template<class T, size_t N>
struct is_array<T[N]> : boost::true_type {};
template<class T>
struct is_array<T[]> : boost::true_type {};

#include <boost/static_assert.hpp>
int main() {
	BOOST_STATIC_ASSERT(is_stdvector<std::vector<char> >::value);
	BOOST_STATIC_ASSERT(!is_stdvector<char>::value);
	BOOST_STATIC_ASSERT(!is_stdvector<int>::value);

	BOOST_STATIC_ASSERT(!is_array<int>::value);
	BOOST_STATIC_ASSERT(is_array<int[]>::value);
	BOOST_STATIC_ASSERT(is_array<int[7]>::value);
	return 0;
}
