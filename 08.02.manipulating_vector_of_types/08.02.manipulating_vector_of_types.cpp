// 08.02.manipulating_vector_of_types.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

// 부호없는 숫자 만들기
struct unsigne; // 오타 아님: `unsigned`는 키워드라서 사용할 수 없다

								// 상수 만들기
struct constant;

// 그외에는 데이터형을 바꾸지 않는다
struct no_change;

// 단계 3에서 필요한 헤더
#include <boost/mpl/size.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

// 단계 4에서 필요한 헤더
#include <boost/mpl/if.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/add_const.hpp>

// 단계 5에서 필요한 헤더
#include <boost/mpl/transform.hpp>

template <class Types, class Modifiers>
struct do_modifications {

	BOOST_STATIC_ASSERT((
		boost::mpl::size<Types>::type::value
		==
		boost::mpl::size<Modifiers>::type::value
		));

	typedef boost::mpl::if_<
		boost::is_same<boost::mpl::_2, unsigne>,
		boost::make_unsigned<boost::mpl::_1>,
		boost::mpl::if_<
		boost::is_same<boost::mpl::_2, constant>,
		boost::add_const<boost::mpl::_1>,
		boost::mpl::_1
		>
	> binary_operator_t;

	// >::type binary_operator_t; // 잘못됨!

	typedef typename boost::mpl::transform<
		Types,
		Modifiers,
		binary_operator_t
	>::type type;
};

/*
void boost_mpl_transform_pseoudocode() {

vector result;
for (std::size_t i = 0; i < Types.size(); ++i) {
result.push_back(
binary_operator_t(Types[i], Modifiers[i])
);
}
return result;
}
*/


#include <boost/mpl/vector.hpp>
typedef boost::mpl::vector<unsigne, no_change, constant, unsigne> modifiers;
typedef boost::mpl::vector<int, char, short, long> types;

typedef do_modifications<types, modifiers>::type result_type;

#include <boost/mpl/at.hpp>

BOOST_STATIC_ASSERT((boost::is_same<
	boost::mpl::at_c<result_type, 0>::type,
	unsigned int
>::value));

BOOST_STATIC_ASSERT((boost::is_same<
	boost::mpl::at_c<result_type, 1>::type,
	char
>::value));

BOOST_STATIC_ASSERT((boost::is_same<
	boost::mpl::at_c<result_type, 2>::type,
	const short
>::value));

BOOST_STATIC_ASSERT((boost::is_same<
	boost::mpl::at_c<result_type, 3>::type,
	unsigned long
>::value));

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES

template <class... T>
struct vt_example {
	typedef typename boost::mpl::vector<T...> type;
};

BOOST_STATIC_ASSERT((boost::is_same<
	boost::mpl::at_c<vt_example<int, char, short>::type, 0>::type,
	int
>::value));

#endif


#include <iostream>
#include <typeinfo>
int main() {
	std::cout << typeid(boost::mpl::size<types>::type).name() << '\n';
}

