// 08.05.LazyEvalMetafunc.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>

using boost::mpl::_1;
using boost::mpl::_2;



// �ǹ̾��� �� ����ü
struct fallback;




//#define USE_INCORRECT_APPLY_IF
#ifdef USE_INCORRECT_APPLY_IF

template <class Func, class Param, class Cond, class Fallback = fallback>
struct apply_if {
	typedef typename boost::mpl::apply<Cond, Param> condition_t;

	// �߸���, `::type`�� ȣ��� �� ��Ÿ �Լ��� �򰡵ȴ�
	typedef typename boost::mpl::apply<Func, Param>::type applied_type;

	typedef typename boost::mpl::if_c<
		condition_t::value,
		applied_type,
		boost::mpl::identity<Fallback>
	>::type type;
};

#else

template <class Func, class Param, class Cond, class Fallback = fallback>
struct apply_if {
	typedef typename boost::mpl::apply<Cond, Param>::type condition_t;

	// '::type' �Ⱦ�
	typedef typename boost::mpl::apply<Func, Param> applied_type;

	typedef typename boost::mpl::eval_if_c<
		condition_t::value,
		applied_type,
		boost::mpl::identity<Fallback>
	>::type type;

};

#endif




// �̰� �� �ߵǴ� �����ϱ� pass
typedef apply_if<
	boost::make_unsigned<_1>,
	int,
	boost::is_integral<_1>
>::type res1_t;
BOOST_STATIC_ASSERT((boost::is_same<res1_t, unsigned int>::value));

// �Լ��� �������� ������ �ʴ´ٸ�
// boost::make_unsigned<_1>�� ���� �ڵ� ���� �� ��򰡿��� ���� ���� �˻翡�� �����Ѵ� (applied_type ��� ��...)
typedef apply_if<
	boost::make_unsigned<_1>,
	float,
	boost::is_integral<_1>
>::type res2_t;
BOOST_STATIC_ASSERT((boost::is_same<res2_t, fallback>::value));


/*
// å�� eval_if_c ���� ���� ���� ������,,, �̰� ���� �����Ϸ�

template<bool C, typename F1, typename F2>
struct eval_if_c {
typedef typename if_c<C,F1,F2>::type f_;
typedef typename f_::type type; // �� �Ķ���Ϳ� ���ؼ��� `::type` ȣ��
};

// * msvc 2015�� ����� ���� �����Ǿ� ���� *

template<bool C, typename F1, typename F2>
struct eval_if_c : if_c<C,F1,F2>::type
{
};

*/

int main() {
	return 0;
}

