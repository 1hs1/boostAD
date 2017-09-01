#pragma once

namespace cpp11
{

	template <class T1, class T2>
	auto my_function_cpp11(const T1& v1, const T2& v2)
		-> decltype(v1 + v2)
	{
		return v1 + v2;
	}

}
