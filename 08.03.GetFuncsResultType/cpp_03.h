#pragma once

#include <boost/type_traits/common_type.hpp>

namespace cpp03
{
	// ����������, c++03 ������ ����� �� �ִ� ���

	namespace result_of {

		template <class T1, class T2>
		struct my_function_cpp03 {
			typedef typename boost::common_type<T1, T2>::type type;
		};

		template <>
		struct my_function_cpp03<s1, s2> {	// ����<s1,s2>�� �����Ǵ� Ÿ�� ����
			typedef s3 type;
		};

		template <>
		struct my_function_cpp03<s2, s1> {	// ����<s2,s1>�� �����Ǵ� Ÿ�� ����
			typedef s3 type;
		};
	} // result_of ���ӽ����̽�

	template <class T1, class T2>
	inline typename result_of::my_function_cpp03<T1, T2>::type
		my_function_cpp03(const T1& v1, const T2& v2)
	{
		return v1 + v2;
	}

}
