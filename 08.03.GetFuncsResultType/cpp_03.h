#pragma once

#include <boost/type_traits/common_type.hpp>

namespace cpp03
{
	// 불편하지만, c++03 에서도 사용할 수 있는 방법

	namespace result_of {

		template <class T1, class T2>
		struct my_function_cpp03 {
			typedef typename boost::common_type<T1, T2>::type type;
		};

		template <>
		struct my_function_cpp03<s1, s2> {	// 인자<s1,s2>에 대응되는 타입 선언
			typedef s3 type;
		};

		template <>
		struct my_function_cpp03<s2, s1> {	// 인자<s2,s1>에 대응되는 타입 선언
			typedef s3 type;
		};
	} // result_of 네임스페이스

	template <class T1, class T2>
	inline typename result_of::my_function_cpp03<T1, T2>::type
		my_function_cpp03(const T1& v1, const T2& v2)
	{
		return v1 + v2;
	}

}
