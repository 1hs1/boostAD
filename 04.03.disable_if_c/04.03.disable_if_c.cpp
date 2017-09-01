// 04.03.disable_if_c.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/has_plus_assign.hpp>


// 모든 가능한 데이터형에 대해 동작할 수 있는 템플릿 함수
//template< class T >
//T process_data(const T& v1, const T& v2, const T& v3)
//{
//	return v1;
//}


// +=
template< class T >
T process_data_plus_assign(const T& v1, const T& v2, const T& v3)
{
	return v1;
}


// process_data의 수정된 일반 버전
template <class T>
typename boost::disable_if_c<boost::has_plus_assign<T>::value, T>::type
	process_data(const T& v1, const T& v2, const T& v3)
{
	return v1;
}


// 이 process_data는 process_data_plus_assign를 호출한다
template <class T>
typename boost::enable_if_c<boost::has_plus_assign<T>::value, T>::type
	process_data(const T& v1, const T& v2, const T& v3)
{
	return process_data_plus_assign(v1, v2, v3);
}



// 첫번째 버전
template <class T>
typename boost::disable_if<boost::has_plus_assign<T>, T>::type
	process_data2(const T& v1, const T& v2, const T& v3);

// process_data_plus_assign
template <class T>
typename boost::enable_if<boost::has_plus_assign<T>, T>::type
	process_data2(const T& v1, const T& v2, const T& v3);


int main()
{
	int i = 1;
	// 최적화된 버전
	process_data(i, i, i);

	// 기본 버전
	// 템플릿 파라미터를 명시적으로 지정
	process_data<const char*>("Testing", "example", "function");

    return 0;
}

