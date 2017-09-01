#pragma once

namespace cpp14
{
	// decltype ¾È½áµµ µÊ

	template <class T1, class T2>
	auto my_function_cpp14(const T1& v1, const T2& v2)
	{
		return v1 + v2;
	}

	static auto my_function_cpp14_lambda = [](auto const & v1, auto const & v2)
	{
		return v1 + v2;
	};

}
