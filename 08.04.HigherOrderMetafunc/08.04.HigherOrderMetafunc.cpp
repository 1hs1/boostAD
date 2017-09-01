// 08.04.HigherOrderMetafunc.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <iostream>


using boost::mpl::_1;	// placeholder �� namespace�� �ٸ�
using boost::mpl::_2;


// ��������1 : �̷��� '������ ��Ÿ �Լ�' ��� �Ѵ�... (�Լ� ��ü�� �����ϰų� ����� �޴�...)
typedef void(*function_t)(int);

function_t higher_order_function1();
void higher_order_function2(function_t f);
function_t higher_order_function3(function_t f);


// ��������2 : mpl::apply�� ù��° ���ڿ� �ش��ϴ� ���ø� �Լ��� �Ķ���͵��� �����Ų ����� ��� ���ø� ���
void what_is_apply()
{
	using namespace boost;
	BOOST_STATIC_ASSERT(mpl::apply<
		mpl::plus<_1, _2>
		, mpl::int_<6>
		, mpl::int_<7>
	>::type::value == 13);
}


// ���� 1
template <class Param1, class Param2, class Func1, class Func2>
struct coalesce {
	typedef typename boost::mpl::apply<Func1, Param1>::type type1;
	typedef typename boost::mpl::apply<Func2, Param2>::type type2;

	typedef typename boost::mpl::if_<
		boost::is_same< boost::mpl::false_, type1>,
		type2,
		type1
	>::type type;
};

typedef coalesce<
	boost::mpl::true_,
	boost::mpl::true_,
	boost::mpl::not_<_1>,
	boost::mpl::not_<_1>
>::type res1_t;
BOOST_STATIC_ASSERT((!res1_t::value));

typedef coalesce<
	boost::is_same<int, short>::type,
	boost::mpl::false_,
	boost::mpl::not_<boost::mpl::not_<_1>>,
	boost::mpl::not_<_1>
>::type res2_t;
BOOST_STATIC_ASSERT((res2_t::value));



int main() {
	std::cout << res1_t::value << '\n';
	std::cout << res2_t::value << '\n';
}

