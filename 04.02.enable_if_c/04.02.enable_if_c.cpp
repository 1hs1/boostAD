// 04.02.enable_if_c.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <iostream>>
using namespace std;

/*
template< class T >
class data_processor
{
	double process(const T& v1, const T& v2, const T& v3)
	{

	}
};


template< class T >
class data_processor
{
	typedef int fast_int_t;
	double process(fast_int_t v1, fast_int_t v2, fast_int_t v3)
	{

	}
};

template< class T >
class data_processor
{
	double process(double v1, double v2, double v3)
	{

	}
};

*/



#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/static_assert.hpp>			//
#include <boost/type_traits/is_same.hpp>	//

// �Ϲ� ����
template <class T, class Enable = void>
class data_processor
{
public:
	double process(const T& /*v1*/, const T& /*v2*/, const T& /*v3*/)
	{
		BOOST_STATIC_ASSERT((boost::is_same<const char*, T>::value));
		return 0.0;
	}
};

// ������ ���� ����
template< class T >
class data_processor< T, typename boost::enable_if_c< boost::is_integral<T>::value >::type >
{
public:
	typedef int fast_int_t;
	double process(fast_int_t v1, fast_int_t v2, fast_int_t v3)
	{
		BOOST_STATIC_ASSERT((boost::is_same<int, T>::value || boost::is_same<short, T>::value));
		return 0.0;
	}
};

// �Ǽ��� ���� ����
template< class T >
class data_processor< T, typename boost::enable_if_c< boost::is_float<T>::value >::type >
{
public:
	double process(double v1, double v2, double v3)
	{
		BOOST_STATIC_ASSERT((boost::is_same<double, T>::value || boost::is_same<float, T>::value));
		return 0.0;
	}
};


template< class T >
double example_func(T v1, T v2, T v3)
{
	data_processor<T> proc;

	cout << typeid(T).name() << endl;

	return proc.process(v1, v2, v3);
}

int main()
{
	// ������ ���� ����
	example_func(1, 2, 3);
	short s = 0;
	example_func(s, s, s);


	// �Ǽ��� ���� ������ ���δ�.
	example_func(1.0, 2.0, 3.0);
	example_func(1.0f, 2.0f, 3.0f);


	// �Ϲ� ������ ���δ�.
	example_func("hello", "word", "processing");

    return 0;
}