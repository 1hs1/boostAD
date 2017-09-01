// 09.02.unordered.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// 비정렬 집합과 맵 사용

#include "stdafx.h"

#include <boost/unordered_map.hpp>

#include <string>
#include <map>
#include <iostream>
#include <assert.h>
#include <boost/lexical_cast.hpp>

#include <boost/unordered_set.hpp>

#include<chrono>

class ElapsedTime : private boost::noncopyable
{
public:
	ElapsedTime()
	{
		m_nStart = std::chrono::system_clock::now();
	}

	~ElapsedTime()
	{
		m_nEnd = std::chrono::system_clock::now();
		std::cout << std::endl;
		std::cout << "elapsed time : " << std::chrono::duration<double>(m_nEnd - m_nStart).count() << "ms" << std::endl;
	}

private:
	//double m_nStart_Time = static_cast<double>(time(NULL));
	std::chrono::system_clock::time_point m_nStart;
	std::chrono::system_clock::time_point m_nEnd;
};

void example() {
	boost::unordered_set<std::string> strings;

	strings.insert("This");
	strings.insert("is");
	strings.insert("an");
	strings.insert("example");

	assert(strings.find("is") != strings.cend());
}

#include <set>
template <class T>
void output_example() {
	T strings;

	strings.insert("CZ"); strings.insert("CD");
	strings.insert("A"); strings.insert("B");

	std::copy(
		strings.begin(),
		strings.end(),
		std::ostream_iterator<std::string>(std::cout, "  ")
	);
}


template <class T>
std::size_t test_default() {
	// 상수
	//const std::size_t ii_max = 20000000;
	const std::size_t ii_max = 20000;
	const std::string s("Test string");

	T map;

	for (std::size_t ii = 0; ii < ii_max; ++ii) {
		map[s + boost::lexical_cast<std::string>(ii)] = ii;
	}

	// 한 번 더 삽입
	for (std::size_t ii = 0; ii < ii_max; ++ii) {
		map[s + boost::lexical_cast<std::string>(ii)] = ii;
	}

	return map.size();
}

struct my_type {
	int         val1_;
	std::string val2_;
};

inline bool operator == (const my_type& v1, const my_type& v2) {
	return v1.val1_ == v2.val1_ && v1.val2_ == v2.val2_;
}

std::size_t hash_value(const my_type& v) {
	std::size_t ret = 0u;

	boost::hash_combine(ret, v.val1_);
	boost::hash_combine(ret, v.val2_);

	return ret;
}


int main() {

	int cmd = 0;
	while (([&cmd]() { std::cout << "Exit[0] InputNum : "; std::cin >> cmd; return (0 != cmd); })())
	{
		switch (cmd) {
		case 1: 
		{
			example();

			std::cout << "boost::unordered_set<std::string> : ";
			output_example<boost::unordered_set<std::string> >();
			std::cout << "\nstd::set<std::string> : ";
			output_example<std::set<std::string> >();
			std::cout << '\n';

			boost::unordered_set<my_type> mt;
			mt.insert(my_type());
		}
		break;
		case 2:
		{
			ElapsedTime etime;
			std::cout << "HASH matched: " << test_default< boost::unordered_map<std::string, std::size_t> >();
		}
		break;
		case 3:
		{
			ElapsedTime etime;
			std::cout << "STD matched: " << test_default<std::map<std::string, std::size_t> >();
		}
		break;
		default: break;
		}

		std::cout << '\n';
	}

	return 0;
}
