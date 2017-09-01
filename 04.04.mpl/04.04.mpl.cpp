// 04.03.mpl.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/mpl/int.hpp>

namespace detail
{
	// 일반 구현
	template <class T, class Tag>
	T process_impl(const T& val, Tag /*무시*/)
	{
		return val;
	}

	// 1 바이트 최적화 구현
	template <class T>
	T process_impl(const T& val, boost::mpl::int_<1> /*무시*/)
	{
		return val;
	}


	// 4 바이트 최적화 구현
	template <class T>
	T process_impl(const T& val, boost::mpl::int_<4> /*무시*/)
	{
		return val;
	}

	// 8 바이트 최적화 구현
	template <class T>
	T process_impl(const T& val, boost::mpl::int_<8> /*무시*/)
	{
		return val;
	}
} // 네임스페이스 detail




// 함수 호출을 분배하기만 한다
template <class T>
T process(const T& val)
{
	BOOST_STATIC_ASSERT((boost::is_pod<T>::value));
	return detail::process_impl(val, boost::mpl::int_<sizeof(T)>());	//< 정수형인 컴파일 시간 값을 저장할 뿐인 빈 클래스
}



// boost::mpl::int_<sizeof(T)> 를 아래와 같이 구현할 수 있다.
template <int Value>
struct int_
{
	static const int value = Value;
	typedef int_<Value> type;
	typedef int value_type;
};

int main()
{
	char ch = 0;
	process(ch);

	int i = 10;
	process(i);

	double d = 3.14;
	process(d);

	short s = 7;
	process(s);

    return 0;
}

