// 09.01.hash.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <winbase.h>

class StopWatch
{
public:
	StopWatch(std::string Function) : m_Function(Function)
	{
		QueryPerformanceFrequency(&m_FreqPerSecond);
		QueryPerformanceCounter(&m_StartFreq);
	}

	~StopWatch()
	{
		LARGE_INTEGER NowFreq;
		QueryPerformanceCounter(&NowFreq);
		uint64_t ElapsedTime = (NowFreq.QuadPart - m_StartFreq.QuadPart) / (m_FreqPerSecond.QuadPart / 1000000);	// 마이크로초
		std::cout << "[STOPWATCH] Function : " << m_Function.c_str() << " ElapsedTime : " << static_cast<float>(ElapsedTime / 1000000.f) << std::endl;
	}

private:
	std::string m_Function;

	// 초당 카운트 수
	LARGE_INTEGER m_FreqPerSecond;

	// 시작 카운트 수
	LARGE_INTEGER m_StartFreq;
};

template <class T>
std::size_t test_default() {
	// 상수
	const std::size_t ii_max = 250000;	// 25만
	const std::string s(
		"Long long long string that "
		"will be used in tests to compare "
		"speed of equality comparisons."
	);

	// 비교할 때 사용할 데이터 만들기
	const T data1[] = {
		T(s),
		T(s + s),
		T(s + ". Whooohooo"),
		T(std::string(""))
	};

	const T data2[] = {
		T(s),
		T(s + s),
		T(s + ". Whooohooo"),
		T(std::string(""))
	};

	const std::size_t data_dimensions = sizeof(data1) / sizeof(data1[0]);

	std::size_t matches = 0u;
	for (std::size_t ii = 0; ii < ii_max; ++ii) {
		for (std::size_t i = 0; i < data_dimensions; ++i) {
			for (std::size_t j = 0; j < data_dimensions; ++j) {
				if (data1[i] == data2[j]) {
					++matches;
				}
			}
		}
	}

	return matches;
}




#include <boost/functional/hash.hpp>

struct string_hash_fast {
	typedef std::size_t comp_type;

	const comp_type     comparison_;
	const std::string   str_;

//#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
//
//	template <class T> struct hash
//		: std::unary_function<T, std::size_t>
//	{
//#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
//		std::size_t operator()(T const& val) const
//		{
//			return hash_value(val);
//		}
//#else
//		std::size_t operator()(T const& val) const
//		{
//			return hash_detail::call_hash<T>::call(val);
//		}
//#endif
//	};

	explicit string_hash_fast(const std::string& s)
		: comparison_(
			boost::hash<std::string>()(s)
		)
		, str_(s)
	{
		std::cout << str_.c_str() << std::endl;
	}
};

inline bool operator == (const string_hash_fast& s1, const string_hash_fast& s2) {
	return s1.comparison_ == s2.comparison_ && s1.str_ == s2.str_;
}

inline bool operator != (const string_hash_fast& s1, const string_hash_fast& s2) {
	return !(s1 == s2);
}

// string_hash_fast 클래스의 네임스페이스에 있어야 함
inline std::size_t hash_value(const string_hash_fast& v) {
	return v.comparison_;
}

int main(int argc, char* argv[]) {

		//assert(
		//	test_default<string_hash_fast>()
		//	==
		//	test_default<std::string>()
		//);
	{
		StopWatch Test1("Hash");
		std::cout << "HASH matched: "
			<< test_default<string_hash_fast>() << std::endl;
	}

	{
		StopWatch Test1("String");
		std::cout << "STD matched: "
			<< test_default<std::string>() << std::endl;
	}

	std::cout << '\n';
	assert(
		boost::hash<string_hash_fast>()(string_hash_fast("test"))
		==
		boost::hash<std::string>()("test")
	);

	std::cout << boost::hash<string_hash_fast>()(string_hash_fast("test")) << std::endl;
	std::cout << boost::hash<std::string>()("test");

	while (1)
	{
		if (_kbhit())
		{
			if (_getch() == 27)	// ESC key
			{
				break;
			}
		}
	}
}

