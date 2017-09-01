// 04.03.mpl.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/mpl/int.hpp>

namespace detail
{
	// �Ϲ� ����
	template <class T, class Tag>
	T process_impl(const T& val, Tag /*����*/)
	{
		return val;
	}

	// 1 ����Ʈ ����ȭ ����
	template <class T>
	T process_impl(const T& val, boost::mpl::int_<1> /*����*/)
	{
		return val;
	}


	// 4 ����Ʈ ����ȭ ����
	template <class T>
	T process_impl(const T& val, boost::mpl::int_<4> /*����*/)
	{
		return val;
	}

	// 8 ����Ʈ ����ȭ ����
	template <class T>
	T process_impl(const T& val, boost::mpl::int_<8> /*����*/)
	{
		return val;
	}
} // ���ӽ����̽� detail




// �Լ� ȣ���� �й��ϱ⸸ �Ѵ�
template <class T>
T process(const T& val)
{
	BOOST_STATIC_ASSERT((boost::is_pod<T>::value));
	return detail::process_impl(val, boost::mpl::int_<sizeof(T)>());	//< �������� ������ �ð� ���� ������ ���� �� Ŭ����
}



// boost::mpl::int_<sizeof(T)> �� �Ʒ��� ���� ������ �� �ִ�.
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

