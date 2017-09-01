// 04.07.Typeof.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <functional>
#include <boost/bind.hpp>
#include <boost/typeof/typeof.hpp>

//const ??? var = boost::bind(std::plus<int>(), _1, _1);
BOOST_AUTO(var, boost::bind(std::plus<int>(), _1, _1));
const auto var1 = boost::bind(std::plus<int>(), _1, _1);

typedef decltype(0.5 + 0.5f) type;
typedef BOOST_TYPEOF(0.5 + 0.5f) type1;


//template<class T1, class T2>
//auto add(const T1& t1, const T2& t2) ->decltype(t1 + t2) {
//    return t1 + t2;
//};

template<class T1, class T2>
BOOST_TYPEOF_TPL(T1() + T2()) add(const T1& t1, const T2& t2) {
	return t1 + t2;
};


#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
BOOST_STATIC_ASSERT((boost::is_same<BOOST_TYPEOF(add(1, 1)), int>::value));


namespace readers_project {
	template <class T1, class T2, class T3>
	struct readers_template_class {};
}

#include <boost/tuple/tuple.hpp>

typedef
readers_project::readers_template_class<int, int, float>
readers_template_class_1;

typedef BOOST_TYPEOF(boost::get<0>(
	boost::make_tuple(readers_template_class_1(), 1)
	)) readers_template_class_deduced;

BOOST_STATIC_ASSERT((
	boost::is_same<
	readers_template_class_1,
	readers_template_class_deduced
	>::value
	));

BOOST_TYPEOF_REGISTER_TEMPLATE(
	readers_project::readers_template_class /*클래스 이름*/,
	3 /*템플릿 클래스 수*/
)

int main() {

	return 0;
}
