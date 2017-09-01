// 04.03.disable_if_c.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/has_plus_assign.hpp>


// ��� ������ ���������� ���� ������ �� �ִ� ���ø� �Լ�
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


// process_data�� ������ �Ϲ� ����
template <class T>
typename boost::disable_if_c<boost::has_plus_assign<T>::value, T>::type
	process_data(const T& v1, const T& v2, const T& v3)
{
	return v1;
}


// �� process_data�� process_data_plus_assign�� ȣ���Ѵ�
template <class T>
typename boost::enable_if_c<boost::has_plus_assign<T>::value, T>::type
	process_data(const T& v1, const T& v2, const T& v3)
{
	return process_data_plus_assign(v1, v2, v3);
}



// ù��° ����
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
	// ����ȭ�� ����
	process_data(i, i, i);

	// �⺻ ����
	// ���ø� �Ķ���͸� ��������� ����
	process_data<const char*>("Testing", "example", "function");

    return 0;
}

